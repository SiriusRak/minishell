/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:05 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/24 13:47:05 by enarindr         ###   ########.fr       */
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
	// ft_exit_2(data);
	return (0);
}

int	ft_exit(char *str)
{
	char	*temp;

	if (!(str[0]))
		return (0);
	temp = ft_strdup(str);
	temp = ft_epure_line(temp, 0, 0);
	if (ft_strncmp(temp, "exit", ft_strlen(temp)) == 0)
	{
		add_history(str);
		free (str);
		free (temp);
		return (1);
	}
	free (temp);
	return (0);
}

void    ft_exit_1(t_data *data)
{
	ft_lstclear_2(&(data->env));
	ft_free_tab(data->path);
	ft_free_data(data);
	printf("exitOOO\n");
	clear_history();
	exit (1);
}

// void    ft_exit_2(t_data *data)
// {
// 	// ft_free_data(data);
// 	(void) data;
// }

void	ft_exit_pipe(char *str, t_data *data)
{
	free (str);
	ft_free_data(data);
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
}
