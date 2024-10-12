/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:47:50 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/12 09:07:26 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_take_pipe(char *str, t_data *data)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	str = ft_epure_line(str);
	if (str[0] && str[0] == '|')
	{
		ft_exit_pipe(str, data);
		return (0);
	}
	printf("%s\n", str);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				i = ft_find_next_quote(str, i, 1, data);
			else if (str[i] == '\"')
				i = ft_find_next_quote(str, i, 2, data);
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

int	ft_get_input(t_data *data)
{
	char	*rd_line;

	ft_clear_input(data);
	rd_line = readline("MINISHELL $ ");
	if ((!rd_line) || ft_exit(rd_line))
		ft_exit_1(data);
	data->input = ft_strdup(rd_line);
	data->history = ft_strjoin_2(data->history, ft_strdup(rd_line));
	if (!ft_take_pipe(rd_line, data))
		return (1);
	if (!ft_check_list(data))
		return (1);
	ft_print_all(data);
	ft_clear_history(data);
	return (1);
}
