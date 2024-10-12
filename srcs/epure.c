/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epure.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:12:01 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/12 09:26:36 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_epure_line(char *str)
{
	int     len;
	int     i;
	int     j;
	char    *new;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (NULL);
	while (str[i] && ft_iswite_space(str[i]))
		i++;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	len = ft_strlen(new) - 1;
	while (ft_iswite_space(new[len]) && len > 0)
	{
		new[len] = '\0';
		len--;
	}
	free(str);
	return (new);
}

void	ft_epure_redir(char *str)
{
	int		i;

	i= 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				i = ft_find_next_quote_2(str, i, 1);
			else if (str[i] == '\"')
				i = ft_find_next_quote_2(str, i, 2);
		}
		while (str[i] && str[i + 1] &&
			(str[i] == ' ' && str[i + 1] == ' ')) 
		{
			ft_strlcpy(&(str[i + 1]), &(str[i + 2]), ft_strlen(&(str[i + 1])));
		}
		i++;
	}
}

void	ft_clear_input(t_data *data)
{
	if (data->input)
	{
		free (data->input);
		data->input = NULL;
	}
}
