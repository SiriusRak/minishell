/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:15:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/04 08:38:48 by enarindr         ###   ########.fr       */
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

void	ft_child_exec(t_data *data, char **env, char **arg)
{
	if (data->signal->pid == 0)
	{
		waiting_signial_cmd(data);
		if (execve(data->list->token->path, arg, env) != 0)
		{
			ft_print_error(data->list->token->path, strerror(errno));
			ft_exit_child(data, 126);
		}
		ft_exit_child(data, 0);
	}
}
