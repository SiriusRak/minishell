/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:21:42 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/10 13:01:06 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_cmd(t_data *data)
{
	char	**env;
	char	**arg;

	env = ft_lst_to_char(data->env, 0);
	arg = ft_lst_to_char(data->list->token->cmd, 0);
	data->signal->pid = fork();
	ft_child_exec(data, env, arg);
	signal_heredoc(data);
	check_after_child(data);
	if (data->saved_fd > 0)
		ft_restore_fd(data, data->saved_fd);
	if (ft_chek_sig_cmd(data))
	{
		ft_free_split(env);
		ft_free_split(arg);
		return (data->return_value);
	}
	ft_free_split(env);
	ft_free_split(arg);
	return (data->return_value);
}

void	ft_child_process(t_data *data, t_d_list *lst)
{
	char	*cmd;

	ft_manage_cmd(data, 1);
	cmd = data->list->token->cmd->content;
	if (ft_is_builtin(cmd))
		ft_execute_builtin(data, cmd);
	else if (!data->checker[0] || !data->checker[1])
		data->return_value = ft_execute_cmd(data);
	data->list = lst;
	free (data->checker);
	ft_exit_child(data, data->return_value);
}

void	ft_parent_process(t_data *data, int nbr, int *fd_in, int *pipe_fd)
{
	close(pipe_fd[1]);
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = pipe_fd[0];
	if (nbr == 0)
		data->last_pid = data->pid;
}

void	ft_execute_pipe(t_data *data, int nbr_cmd)
{
	int			i;
	int			pipe_fd[2];
	int			fd_in;
	t_d_list	*lst;

	i = 0;
	fd_in = 0;
	lst = data->list;
	while (i < nbr_cmd)
	{
		pipe(pipe_fd);
		data->pid = fork();
		if (data->pid == 0)
		{
			ft_check_redir(data, pipe_fd, fd_in, i - nbr_cmd + 2);
			ft_manage_fd(pipe_fd, fd_in, i - nbr_cmd + 1, data);
			ft_child_process(data, lst);
		}
		else if (data->pid != 0)
			ft_parent_process(data, nbr_cmd - i - 1, &fd_in, pipe_fd);
		data->list = data->list->next;
		i++;
	}
	ft_wait_pid(data, nbr_cmd, fd_in);
	data->list = lst;
}

void	ft_execute(t_data *data)
{
	int		nbr_cmd;
	char	*cmd;

	nbr_cmd = ft_dlstsize(data->list);
	if (nbr_cmd == 1)
	{
		if (ft_check_redir(data, NULL, 0, 0))
			return ;
		if (ft_manage_cmd(data, 0))
			return ;
		cmd = data->list->token->cmd->content;
		if (!data->checker[0] && !data->checker[1])
		{
			if (ft_is_builtin(cmd) && !data->checker[1])
				ft_execute_builtin(data, cmd);
			else if (!ft_is_builtin(cmd) && !data->checker[1])
				ft_execute_cmd(data);
		}
		free(data->checker);
		close (STDIN_FILENO);
		open ("/dev/tty", O_RDONLY);
	}
	else if (nbr_cmd > 0)
		ft_execute_pipe(data, nbr_cmd);
}
