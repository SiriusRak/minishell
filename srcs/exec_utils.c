/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:02:05 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/28 16:55:52 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

int	ft_check_fd_dup(int fd, int dup, char *s)
{
	if (fd < 0)
	{
		if (errno == EACCES)
			ft_print_error(s, "Permission denied\n");
		else if (errno == EBADF)
			ft_print_error(s, "Bad file descriptor\n");
		else if (errno == ENOENT)
			ft_print_error(s, "No such file or directory\n");
		return (1);
	}
	if (dup < 0)
	{
		perror("Eto hafa");
		close(fd);
		return (1);
	}
	return (0);
}

void   ft_redir(t_data *data, t_list *out, int i)
{
	int	fd;

	if (i == 0)
		data->saved_fd = dup(STDOUT_FILENO);
	while (out)
	{
		if (out->type == OUT)
			fd = open((char *)out->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (out->type == OUT_2)
			fd = open((char *)out->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		data->return_value = ft_check_fd_dup(fd, 0, (char *)out->content);
		if (out->next)
			close(fd);
		out = out->next;
	}
	ft_check_fd_dup(0, dup2(fd, STDOUT_FILENO), "test");
	if (fd != 0)
		close(fd);
}

int	ft_redir_input(t_list *in)
{
	int	fd;

	while (in)
	{
		fd = open((char *)in->content, O_RDONLY);
		if (ft_check_fd_dup(fd, 0, (char *)in->content))
			return (1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("Dup");
			if (fd != 0)
				close(fd);
			return (1);
		}
		if (fd != 0)
			close(fd);
		in = in->next;
	}
	return (0);
}

int	ft_check_path(t_d_list *list)
{
	char	*big;
	char	*path;

	big = ft_strdup(list->token->cmd->content);
	if (!ft_strncmp(big, "/bin/", 5) || access(big, X_OK) == 0)
	{
		list->token->path = ft_strdup(big);
		free(big);
		return (1);
	}
	else
	{
		path = ft_find_in_path(big);
		if (path)
		{
			list->token->path = ft_strdup(path);
			free(big);
			free(path);
			return (1);
		}
	}
	free(big);
	free(path);
	return (0);
}

int	ft_check_cmd(t_data *data, int is_dir, int c)
{
	char		*cmd;
	int			checker;

		checker = 0;
		cmd = ft_strdup(data->list->token->cmd->content);
		if (ft_is_builtin((char *)data->list->token->cmd->content))
			checker = 1;
		else if (ft_check_path(data->list) && checker == 0)
			checker = 1;
		else
		{
			if (!is_dir)
				ft_putstr_fd("minishell: command not found\n", 2);
			free (cmd);
			if (!c)
				return (127);
			else
				ft_exit_child(data, 127);
		}
		free(cmd);
	return (0);
}
