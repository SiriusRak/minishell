/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:21:42 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/26 11:23:26 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_cmd(t_data *data)
{
	char	**env;
	char	**arg;

	if (!data->path)
	{
		perror("path");
		return ;
	}
	env = ft_lst_to_char(data->env, 0);
	if (ft_strncmp(data->list->token->cmd->content, "clear", 5) == 0)
		printf ("\n");
	arg = ft_lst_to_char(data->list->token->cmd, 0);
	data->signal->pid = fork();
	if (data->signal->pid == 0)
	{
		waiting_signial_cmd(data);
		if (data->list->token->out != NULL)
			ft_redir(data, data->list->token->out);
		if (execve(data->list->token->path, arg, env) != 0)
			perror("execve");
		ft_exit_child(data, 0);
	}
	signal_heredoc(data);
	check_after_child(data);
	wait(0);
	if (ft_chek_sig(data))
		return ;
	ft_free_split(env);
	ft_free_split(arg);
}
void	ft_child_process(t_data *data, int fd_in, int *pipe_fd, int i)
{
	char	*cmd;
	
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	if (i > 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	cmd = ft_strdup(data->list->token->cmd->content);
	if (ft_is_builtin(cmd))
	{
		ft_execute_builtin(data, cmd);
		exit(0);
	}
	else if (!ft_is_builtin(cmd))
		ft_execute_cmd(data);
	free(cmd);
}

void	ft_parent_process(int *fd_in, int *pipe_fd)
{
	wait(NULL);
	close(pipe_fd[1]);
	*fd_in = pipe_fd[0];
}

void	ft_execute_pipe(t_data *data, int nbr_cmd)
{
	int		i;
	int		pipe_fd[2];
	int		fd_in;
	t_d_list *lst;
	t_cmd	check;

	i = 0;
	fd_in = 0;
	lst = data->list;
	while (i < nbr_cmd)
	{
		pipe(pipe_fd);
		data->pid = fork();
		if (data->pid == 0)
		{
			if (data->list->token->out != NULL)
				ft_redir(data, data->list->token->out);
			if (data->list->token->in != NULL)
				ft_redir_input(data->list->token->in);
			check.is_dir = ft_isdir(data->list->token->cmd->content);
			check.is_cmd = ft_check_cmd(data, check.is_dir, 1);
			dup2(fd_in, STDIN_FILENO);
			if (i < nbr_cmd - 1)
				dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			if (ft_is_builtin(data->list->token->cmd->content))
			{
				ft_execute_builtin(data, data->list->token->cmd->content);
				data->list = lst;
				ft_exit_child(data, 0);
			}
			else if (!check.is_cmd || !check.is_dir)
			{
				ft_execute_cmd(data);
				data->list = lst;
				ft_exit_child(data, 0);
			}
		}
		else if (data->pid != 0)
		{
			close(pipe_fd[1]);
			if (fd_in != 0)
				close(fd_in);
			fd_in = pipe_fd[0];
		}
		data->list = data->list->next;
		i++;
	}
	i = 0;
	while (i++ < nbr_cmd)
		wait(NULL);
	if (fd_in != 0)
		close(fd_in);
	data->list = lst;
}

void	ft_execute(t_data *data)
{
	int		is_cmd;
	int		nbr_cmd;
	int		is_dir;

	nbr_cmd = ft_dlstsize(data->list);
	if (nbr_cmd == 1 && data->list->token->cmd)
	{
		is_dir = ft_isdir(data->list->token->cmd->content);
		is_cmd = ft_check_cmd(data, is_dir, 0);
		data->return_value = is_cmd;
		if (data->list->token->in != NULL)
			ft_redir_input(data->list->token->in);
		if (ft_is_builtin((char *)data->list->token->cmd->content) && !is_cmd)
			ft_execute_builtin(data, data->list->token->cmd->content);
		else if (!ft_is_builtin((char *)data->list->token->cmd->content) && !is_cmd)
			ft_execute_cmd(data);
		close (STDIN_FILENO);
		open ("/dev/tty", O_RDONLY);
	}
	else if (nbr_cmd > 0)
		ft_execute_pipe(data, nbr_cmd);
}
