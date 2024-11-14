/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epure.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:12:01 by enarindr          #+#    #+#             */
/*   Updated: 2024/11/14 13:26:51 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

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
	int     len;
	char    *new;

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

int		epure_space_ext(char **nw_str, char **sr, int *j, int *i)
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
	return  (0);
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
	return(new_str);
}

void	ft_clear_input(t_data *data)
{
	if (data->input)
	{
		free (data->input);
		data->input = NULL;
	}
}

char	*ft_arrange_prev_redir_ext(char *str, int i)
{
	char	*prev;
	char	*next;
	char	*new;

	prev = ft_substr(str, 0, i);
	prev = ft_strjoin_2(prev, ft_strdup(" "));
	next = ft_substr(str, i, ft_strlen(str) - i);
	free (str);
	new = ft_strjoin_2(prev, next);
	return (new);
}

char	*ft_arrange_prev_redir(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_find_next_quote_2(str, i, str[i]);
		if (str[i] == '<' || str[i] == '>')
		{
			c = str[i];
			if (i > 0)
			{
				if (str[i - 1] != ' ' && str[i - 1] != c)
					str = ft_arrange_prev_redir_ext(str, i);
			}
			i++;
		}
		else
			i++;
	}
	return (str);
}

char	*ft_arrange_back_redir(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_find_next_quote_2(str, i, str[i]);
		if (str[i] == '<' || str[i] == '>')
		{
			c = str[i++];
			if (str[i] == c)
				i++;
			if (str[i] && str[i] != ' ')
			{
				str = ft_arrange_prev_redir_ext(str, i);
				i++;
			}
		}
		else
			i++;
	}
	return (str);
}

char	*ft_epure_redir(char *str)
{
	char	*new;

	new = ft_strdup(str);
	new = ft_arrange_prev_redir(new);
	new = ft_arrange_back_redir(new);
	free (str);
	return (new);
}
