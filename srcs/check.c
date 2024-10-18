/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:20:39 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/15 16:55:36 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_error(char *str)
{
	if (str[0] == '<' || str[0] == '>')
	{
		ft_putstr_fd("MINISHELL: syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		write(2, "'\n", 2);
		return (0);
	}
	return (1);
}

int	ft_notsep(char	c)
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

int	ft_iswite_space(char c)
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
