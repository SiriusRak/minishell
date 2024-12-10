/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:15:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/10 10:40:06 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_wait_pid(t_data *data, int nbr_cmd, int fd_in)
{
	int	i;

	i = 0;
	while (i++ < nbr_cmd)
	{
		data->pid = waitpid(-1, &data->status, 0);
		if (data->pid > 0)
		{
			if (WIFEXITED(data->status) && data->pid == data->last_pid)
				data->return_value = WEXITSTATUS(data->status);
		}
	}
	if (fd_in != 0)
		close(fd_in);
}

void	ft_child_exec(t_data *data, char **env, char **arg)
{
	if (data->signal->pid == 0)
	{
		waiting_signial_cmd(data);
		if (execve(data->list->token->path, arg, env) != 0)
		{
			ft_print_error(data->list->token->path, strerror(errno));
			ft_exit_child(data, 126);
		}
		ft_exit_child(data, 0);
	}
}

void	ft_inputerror(int *pipe_fd, int fd_in)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}
