/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:02:05 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/23 16:34:59 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_fd_dup(int fd, int dup)
{
	if (fd < 0)
	{
		perror("open");
	}
	if (dup < 0)
	{
		perror("dup2");
	}
}

void    ft_redir(t_list *out, int type)
{
	int	fd;

	while (out && type == 1)
	{
		fd = open((char *)out->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("%d %s\n", fd, (char *)out->content);
		ft_check_fd_dup(fd, 0);
		out = out->next;
	}
	while (out && type == 2)
	{
		fd = open((char *)out->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_check_fd_dup(fd, 0);
		out = out->next;
	}
	ft_check_fd_dup(0, dup2(fd, STDOUT_FILENO));
	printf("Mccccccccccccccc\n");
	close(fd);
	exit(0);
}
