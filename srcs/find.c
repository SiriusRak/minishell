/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:51:02 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/12 08:14:56 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_find_next_quote(char *str, int start, int type, t_data *data)
{
	char	c;

	start++;

	if (type == 1)
		c = '\'';
	else if (type == 2)
		c = '\"';
	while (str[start] && str[start] != c)
		start++;
	if (!str[start])
    {
		ft_exit_quote(str, data);
        return (0);
    }
	return (start);	
		
}

int		ft_find_next_quote_2(char *str, int start, int type)
{
	char	c;

	start++;

	if (type == 1)
		c = '\'';
	else if (type == 2)
		c = '\"';
	while (str[start] && str[start] != c)
		start++;
	if (!str[start])
        return (0);
	return (start);	
		
}
