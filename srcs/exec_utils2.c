/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:27:07 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/24 11:06:34 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdir(t_data *data)
{
	t_d_list	*head;
	char		*cmd;
	int			checker;
	struct stat	path_stat;

	head = data->list;
	checker = 0;
	while (head && head->token->cmd)
	{
		cmd = ft_strdup(head->token->cmd->content);
		if(stat(cmd, &path_stat) != 0)
			return (0);
		if (S_ISDIR(path_stat.st_mode))
		{
			printf("minishell: %s: Is a directory\n", cmd);
			checker = 1;
		}
		head = head->next;
		free(cmd);
	}
	if (checker)
		return (1);
	return (0);
}
