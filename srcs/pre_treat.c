/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_treat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:48:43 by enarindr          #+#    #+#             */
/*   Updated: 2024/11/28 17:17:21 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdio.h>

int	ft_readline(t_data *data)
{
	char	* rd_line;

	waiting_signial_here(data);
	close((data->signal->fd)[0]);
	rd_line = readline("MINISHELL $ ");
	if (!rd_line)
		rd_line = ft_strdup("exit");
	write((data->signal->fd)[1], rd_line, ft_strlen(rd_line));
	close((data->signal->fd)[1]);
	free (rd_line);
	ft_exit_child(data, 0);
    return (0);
}

int	ft_chek_sig(t_data *data)
{
	if (data->error == 1)
	{
		printf("\n");
		return (1);
	}
	return (0);
}

int	ft_pipe(t_data *data)
{
	char	*rd_line;

	close((data->signal->fd)[0]);
	waiting_signial_here(data);
	rd_line = readline("PiPe $ ");
	if (!rd_line)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
		close((data->signal->fd)[1]);
		ft_exit_1(data, 1);
	}
	write((data->signal->fd)[1], rd_line, ft_strlen(rd_line));
	close((data->signal->fd)[1]);
	free (rd_line);
	ft_exit_child(data, 0);
    return (0);
}

int pre_treat(t_data *data, int i)
{
	char	*rd_line;

	rd_line = take_script((data->signal->fd)[0]);
	if (!rd_line)
		return (2);
	close((data->signal->fd)[0]);
	// if (ft_exit(rd_line))
	// 	ft_exit_1(data);
	data->input = ft_strdup(rd_line);
	if (i == 1)
		data->history = ft_strjoin_2(data->history, ft_strdup(" "));
	data->history = ft_strjoin_2(data->history, ft_strdup(rd_line));
	if (!ft_take_pipe(rd_line, data))
	{
		data->return_value = 2;
		return (2);
	}
	if (!ft_check_list(data))
		return (2);
	ft_add_back_list(&data->list, data->temp_list);
	// free (data->temp_list);
	data->temp_list = NULL;
	return (0);
}
