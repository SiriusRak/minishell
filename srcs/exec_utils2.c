/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:27:07 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/26 11:23:40 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdir(char *cmd)
{
	struct stat	path_stat;

	if(stat(cmd, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
	{
		printf("minishell: %s: Is a directory\n", cmd);
		return (1);
	}
	return (0);
}
