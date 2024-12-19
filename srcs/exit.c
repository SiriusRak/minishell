/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:05 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/19 15:55:48 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <stdio.h>

int	ft_exit_quote(char *str, t_data *data)
{
	free (str);
	printf("**history**: %s\n", data->history);
	ft_putstr_fd("unclosed quote\n", 2);
	return (0);
}

void	ft_exit_1(t_data *data, int exit_code)
{
	ft_lstclear_2(&(data->env));
	ft_free_data(data);
	clear_history();
	free (data->signal);
	exit (exit_code);
}

void	ft_exit_child(t_data *data, int exit_code)
{
	if (data->temp_list)
	{
		ft_free_t_d_list(data->temp_list);
		data->temp_list = NULL;
	}
	ft_lstclear_2(&(data->env));
	ft_free_data(data);
	ft_clear_history(data);
	clear_history();
	free (data->signal);
	exit (exit_code);
}

void	ft_exit_pipe(char *str, t_data *data)
{
	free (str);
	ft_free_data(data);
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
}

int	pre_treat_ext(t_data *data)
{
	data->return_value = 2;
	return (2);
}
