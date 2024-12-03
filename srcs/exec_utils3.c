/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:15:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/03 15:18:09 by rdiary           ###   ########.fr       */
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
