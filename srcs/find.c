/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:51:02 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/04 14:11:58 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_next_quote(char *str, int start, char c, t_data *data)
{
	start++;
	while (str[start] && str[start] != c)
		start++;
	if (!str[start])
	{
		ft_exit_quote(str, data);
		return (0);
	}
	return (start);
}

int	ft_find_next_quote_2(char *str, int start, char c)
{
	start++;
	while (str[start] && str[start] != c)
		start++;
	if (!str[start])
		return (0);
	return (start);
}
