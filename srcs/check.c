/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:20:39 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/11 12:52:02 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_notsep(char	c)
{
	int		i;
	char	*sep;

	i = 0;
	sep = ft_strdup(" ;\'\"$<>|");
	while (sep[i])
	{
		if (sep[i] == c)
		{
			free (sep);
			return (0);
		}
		i++;
	}
	free (sep);
	return (1);
}

int		ft_iswite_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_end_pip(char *str)
{
	if (str[ft_strlen(str) - 1] == '|')
		return (1);
	return (0);
}
