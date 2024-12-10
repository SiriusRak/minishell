/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:23:50 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/08 11:24:56 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_clean_quote(t_d_list *list, char *str, int type)
{
	int		i;
	char	c;

	i = 0;
	while (str && str[i])
	{
		c = str[i];
		if (str[i] == '\"' || str[i] == '\'')
		{
			i = ft_clean(&list, &str, i, type);
			if (str[i] && str[i] == c)
			{
				str = ft_clean_ext(str, i);
			}
		}
		else if ((str[i] == '$' && type != HERE) || (str[i] == '~'
				&& (!str[i + 1] || (str[1 + 1] && str[i + 1] == '/'))))
			i = ft_expand(list, &str, i, 0);
		else
			i++;
	}
	return (str);
}
