/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:47:50 by enarindr          #+#    #+#             */
/*   Updated: 2024/11/05 19:13:45 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	ft_take_pipe(char *str, t_data *data)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	str = ft_epure_line(str, 0, 0);
	if (!str)
		return (0);
	if (str[0] && str[0] == '|')
	{
		ft_exit_pipe(str, data);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = ft_find_next_quote(str, i, str[i], data);
			if (!i)
				return (0);
		}
		if (str[i] && str[i] == '|')
		{
			if (ft_pipe_error(str, i))
			{
				ft_exit_pipe(str, data);
				return (0);
			}
			i = ft_add_list(data, start, i, str);
			start = i + 1;
		}
		i++;
	}
	if (start < i)
		ft_add_list(data, start, i, str);
	free(str);
	return (1);
}

int	ft_end_of_pipe(char *str)
{
	if (str[ft_strlen(str) - 1] == '|')
		return (1);
	return (0);
}

int	ft_get_input(t_data *data)
{
	char	*rd_line;

	rd_line = readline("MINISHELL $ ");
	if ((!rd_line) || ft_exit(rd_line))
		ft_exit_1(data);
	data->input = ft_strdup(rd_line);
	data->history = ft_strjoin_2(data->history, ft_strdup(rd_line));
	if (!ft_take_pipe(rd_line, data))
	{
		data->return_value = 2;
		return (2);
	}
	if (!ft_check_list(data))
	{
		data->return_value = 2;
		return (2);
	}
	ft_add_back_list(&data->list, data->temp_list);
	data->temp_list = NULL;
	while (ft_end_of_pipe(data->input))
	{
		data->error = 0;
		// signal_heredoc(data);
		free(data->input);
		rd_line = readline("PiPe $ ");
		if (!rd_line)
		{
			ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
			ft_exit_1(data);
		}
		data->input = ft_strdup(rd_line);
		data->history = ft_strjoin_2(data->history, ft_strdup(" "));
		data->history = ft_strjoin_2(data->history, ft_strdup(rd_line));
		if (!ft_take_pipe(rd_line, data))
			return (2);
		if (!ft_check_list(data))
			return (2);
		ft_add_back_list(&data->list, data->temp_list);
		data->temp_list = NULL;
		if (data->error == 1)
			return  (130);
	}
	if (data->error == 1)
	{
		data->return_value = 130;
		return  (130);
	}
	ft_print_all(data);
	ft_execute(data);
	return (0);
}
