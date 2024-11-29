/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:27:07 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/29 08:38:33 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdir(t_data *data, char *cmd, int c)
{
	struct stat	path_stat;

	if(stat(cmd, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_print_error(cmd, "Is a directory\n");
		if (!c)
			data->return_value = 126;
		else
			ft_exit_child(data, 126);
		return (1);
	}
	return (0);
}
