/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:27:07 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/29 14:59:11 by rdiary           ###   ########.fr       */
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
			data->return_value = err;
		else
			ft_exit_child(data, err);
	}
}

int	ft_isdir(t_data *data, char *cmd, int c)
{
	struct stat	path_stat;

	if(stat(cmd, &path_stat) != 0)
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
			ft_exit_child(data, 126);
		return (1);
	}
	return (0);
}
