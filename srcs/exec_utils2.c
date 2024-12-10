/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:27:07 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/10 11:06:27 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_manage_error(t_data *data, char *cmd, int err, int c)
{
	if (errno == ENOENT)
	{
		ft_print_error(cmd, "No such file or directory");
		if (!c)
			data->return_value = 127;
		else
			ft_exit_child(data, 127);
	}
	else if (errno == ENOTDIR)
	{
		ft_print_error(cmd, "Not a directory");
		if (!c)
			data->return_value = 126;
		else
			ft_exit_child(data, 126);
	}
	else
	{
		ft_print_error(cmd, strerror(err));
		if (!c)
			data->return_value = 126;
		else
			ft_exit_child(data, 126);
	}
}

int	ft_isdir(t_data *data, char *cmd, int c)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) != 0)
	{
		ft_manage_error(data, cmd, errno, c);
		return (-1);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_print_error(cmd, "Is a directory");
		if (!c)
			data->return_value = 126;
		else
		{
			free(data->checker);
			ft_exit_child(data, 126);
		}
		return (1);
	}
	return (0);
}

int	*ft_manage_exec(t_data *data, char *cmd, int i)
{
	data->checker = malloc(sizeof(int) * 2);
	if (ft_strchr(cmd, '/'))
		data->checker[0] = ft_isdir(data, cmd, i);
	else
		data->checker[0] = 0;
	if (!data->checker[0])
	{
		if (cmd[0] != '\0')
			data->checker[1] = ft_check_cmd(data, cmd, data->checker[0], i);
		else
		{
			ft_print_error(cmd, "command not found");
			data->checker[1] = 127;
		}
		data->return_value = data->checker[1];
	}
	return (data->checker);
}

int	ft_check_redir(t_data *data, int *pipe_fd, int fd_in, int i)
{
	if (!i)
	{
		if (data->list->token->out != NULL)
			ft_redir(data, data->list->token->out, 0);
		if (data->list->token->in != NULL)
		{
			data->return_value = ft_redir_input(data->list->token->in);
			if (data->return_value)
				return (1);
		}
	}
	else
	{
		if (data->list->token->out != NULL)
			ft_redir(data, data->list->token->out, 1);
		if (data->list->token->in != NULL)
		{
			if (ft_redir_input(data->list->token->in))
			{
				ft_inputerror(pipe_fd, fd_in);
				ft_exit_child(data, 1);
			}
		}
	}
	return (0);
}

void	ft_manage_fd(int *pipe_fd, int fd_in, int i, t_data *data)
{
	if (fd_in != 0 && !data->list->token->in)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (i != 0 && !data->list->token->out)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
