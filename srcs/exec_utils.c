/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:02:05 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/04 14:29:44 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

int	ft_check_fd_dup(int fd, int dup, char *s)
{
	if (fd < 0)
	{
		if (errno == EACCES)
			ft_print_error(s, "Permission denied");
		else if (errno == EBADF)
			ft_print_error(s, "Bad file descriptor");
		else if (errno == ENOENT)
			ft_print_error(s, "No such file or directory");
		return (1);
	}
	if (dup < 0)
	{
		perror("dup");
		close(fd);
		return (1);
	}
	return (0);
}

void	ft_redir(t_data *data, t_list *out, int i)
{
	int		fd;
	char	*out_t;

	if (i == 0)
		data->saved_fd = dup(STDOUT_FILENO);
	while (out)
	{
		out_t = (char *)out->content;
		if (out->type == OUT)
			fd = open(out_t, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (out->type == OUT_2)
			fd = open(out_t, O_WRONLY | O_CREAT | O_APPEND, 0644);
		data->return_value = ft_check_fd_dup(fd, 0, (char *)out->content);
		if (out->next)
			close(fd);
		out = out->next;
	}
	ft_check_fd_dup(0, dup2(fd, STDOUT_FILENO), out_t);
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

int	ft_check_path(t_data *data, t_d_list *list)
{
	char	*big;
	char	*path;

	big = ft_strdup(list->token->cmd->content);
	if (!ft_strncmp(big, "/bin/", 5) || (access(big, X_OK) == 0
			&& ft_strchr(big, '/')))
	{
		list->token->path = ft_strdup(big);
		free(big);
		return (1);
	}
	else
	{
		path = ft_find_in_path(data, big);
		if (path)
		{
			list->token->path = ft_strdup_2(path);
			free(big);
			return (1);
		}
	}
	free(big);
	free(path);
	return (0);
}

int	ft_check_cmd(t_data *data, char *cmd, int is_dir, int c)
{
	data->checker[1] = 0;
	if (ft_is_builtin(cmd))
		data->checker[1] = 1;
	else if (ft_check_path(data, data->list) && data->checker[1] == 0)
		data->checker[1] = 1;
	else
	{
		if (!data->path)
			ft_print_error(cmd, "No such file or directory");
		if (!is_dir && data->path)
			ft_print_error(cmd, "command not found");
		else
			return (126);
		if (!c)
			return (127);
		else
			ft_exit_child(data, 127);
	}
	return (0);
}
