/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:21:42 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/19 14:34:23 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_cmd(t_data *data)
{
	char	**env;
	char	**arg;
	pid_t	pid;

	env = ft_lst_to_char(data->env, 0);
	arg = ft_lst_to_char(data->list->token->cmd, 1);
	pid = fork();
	if (pid == 0)
	{
		if (data->list->token->out != NULL)
			ft_redir(data->list->token->out);
		if (execve(data->list->token->path, arg, env) != 0)
			perror("execve");
		exit (1);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");
	
	ft_free_split(env);
	ft_free_split(arg);
}
void	ft_child_process(t_data *data, int fd_in, int *pipe_fd, int i)
{
	char	*cmd;
	int		is_cmd;
	
	dup2(fd_in, STDIN_FILENO);
	if (i > 0)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	cmd = ft_strdup(data->list->token->cmd->content);
	is_cmd = ft_check_cmd(data);
	if (ft_is_builtin(cmd) && is_cmd)
	{
		ft_execute_builtin(data, cmd);
		exit(0);
	}
	else if (!ft_is_builtin(cmd) && is_cmd)
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
	pid_t	pid;

	i = 0;
	fd_in = 0;
	while (i++ < nbr_cmd)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			// exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
			ft_child_process(data, fd_in, pipe_fd, nbr_cmd - i);
		else
			ft_parent_process(&fd_in, pipe_fd);
	}
}

void	ft_execute(t_data *data)
{
	char	**arg;
	int		is_cmd;
	int		nbr_pipe;

	nbr_pipe = ft_dlstsize(data->list) - 1;
	if (nbr_pipe == 0)
	{
		// if (data->list->token->out != NULL)
		// 	ft_redir(data->list->token->out);
		arg = ft_lst_to_char(data->list->token->cmd, 1);
		is_cmd = ft_check_cmd(data);
		if (ft_is_builtin((char *)data->list->token->cmd->content) && is_cmd)
			ft_execute_builtin(data, data->list->token->cmd->content);
		else if (!ft_is_builtin((char *)data->list->token->cmd->content) && is_cmd)
			ft_execute_cmd(data);
	}
	else if (nbr_pipe > 0)
		ft_execute_pipe(data, nbr_pipe + 1);
	ft_free_split(arg);
}
