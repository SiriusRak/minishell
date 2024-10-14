/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:02:05 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/14 16:23:48 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_fd_dup(int fd, int dup)
{
	if (fd < 0)
	{
		perror("open");
		// free
	}
	if (dup < 0)
	{
		perror("dup2");
		// free
	}
}

void    ft_redir(t_list *out, int type)
{
	int	fd;

	while (out)
	{
		if (type == 1)
			fd = open((char *)out->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (type == 2)
			fd = open((char *)out->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_check_fd_dup(fd, 0);
		out = out->next;
	}
	ft_check_fd_dup(0, dup2(fd, STDOUT_FILENO));
	close(fd);
	exit(0);
}

int	ft_check_path(t_d_list *list)
{
	char	*big;

	big = ft_strdup(list->token->cmd->content);
	if (ft_strnstr(big, "/bin/", 5))
	{
		if (access(big, X_OK) == 0)
		{
			list->token->path = ft_strdup(big);
			// ft_lstadd_front(&(list->token->arg), ft_lstnew(list->token->cmd->content))
			free(big);
			return (1);
		}
	}
	else
	{
		list->token->path = ft_find_in_path(big);
		if (list->token->path)
		{
			ft_lstadd_front(&(list->token->arg), ft_lstnew(big));
			free(big);
			return (1);
		}
	}
	free(big);
	return (0);
}
int	ft_check_cmd(t_data *data)
{
	t_d_list	*head;
	char		*cmd;
	int			checker;

	head = data->list;
	checker = 0;
	while (head)
	{
		cmd = ft_strdup(head->token->cmd->content);
		if (ft_is_builtin((char *)head->token->cmd->content))
			checker = 1;
		else if (ft_check_path(head) && checker == 0)
			checker = 1;
		else
		{
			perror("cmd");
			return (0);
		}
		head = head->next;
		free(cmd);
	}
	return (1);
}
