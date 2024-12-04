/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epure.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:12:01 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/04 14:26:47 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_epure_ext(char *new, int len)
{
	while (new[len] && ft_iswite_space(new[len]) && len > 0)
	{
		new[len] = '\0';
		len--;
	}
	return (0);
}

char	*ft_epure_line(char *str, int i, int j)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	if (len == 0)
	{
		free(str);
		return (NULL);
	}
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (NULL);
	while (str[i] && ft_iswite_space(str[i]))
		i++;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	len = ft_strlen(new) - 1;
	if (len > 0)
		ft_epure_ext(new, len);
	free(str);
	return (new);
}

int	epure_space_ext(char **nw_str, char **sr, int *j, int *i)
{
	char	*new_str;
	char	*str;
	char	c;

	str = *sr;
	c = str[(*i)];
	new_str = *nw_str;
	new_str[(*j)++] = str[(*i)++];
	while (str[(*i)] != c)
		new_str[(*j)++] = str[(*i)++];
	new_str[(*j)++] = str[(*i)++];
	if (ft_iswite_space(str[(*i)]))
	{
		new_str[(*j)++] = ' ';
		i++;
	}
	return (0);
}

char	*ft_epure_space(char *str, int i, int j)
{
	char	*new_str;

	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			epure_space_ext(&new_str, &str, &j, &i);
		else if (str[i] && !ft_iswite_space(str[i]))
		{
			while (str[i] && !ft_iswite_space(str[i])
				&& str[i] != '\'' && str[i] != '\"')
				new_str[j++] = str[i++];
			if (ft_iswite_space(str[i]))
				new_str[j++] = ' ';
		}
		else
			i++;
	}
	free (str);
	new_str[j] = '\0';
	return (new_str);
}
