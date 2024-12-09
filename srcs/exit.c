/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:05 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/09 08:09:42 by enarindr         ###   ########.fr       */
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
	ft_lstclear_2(&(data->env));
	ft_clear_history(data);
	ft_free_data(data);
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
