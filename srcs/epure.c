/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epure.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:12:01 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/14 20:32:18 by enarindr         ###   ########.fr       */
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

char	*ft_epure_space(char *str)
{
	char	*new_str;
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				c = '\'';
			else if (str[i] == '\"')
				c = '\"';
			new_str[j++] = str[i++];
			while (str[i] != c)
				new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			if (ft_iswite_space(str[i]))
			{
				new_str[j++] = ' ';
				i++;
			}
		}
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

char	*ft_arrange_prev_redir(char *str)
{
	int		i;
	char	*prev;
	char	*next;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				i = ft_find_next_quote_2(str, i, 1);
			else if (str[i] == '\"')
				i = ft_find_next_quote_2(str, i, 2);
		}
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i] == '<')
				c = '<';
			else if (str[i] == '>')
				c = '>';
			if (i > 0)
			{
				if (str[i - 1] != ' ' && str[i - 1] != c)
				{
					prev = ft_substr(str, 0, i);
					prev = ft_strjoin_2(prev, ft_strdup(" "));
					next = ft_substr(str, i, ft_strlen(str) - i);
					free (str);
					str = ft_strjoin_2(prev, next);
				}
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
	char	*prev;
	char	*next;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				i = ft_find_next_quote_2(str, i, 1);
			else if (str[i] == '\"')
				i = ft_find_next_quote_2(str, i, 2);
		}
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i] == '<')
				c = '<';
			else if (str[i] == '>')
				c = '>';
			i++;
			if (str[i] == c)
				i++;
			if (str[i] != ' ')
			{
				prev = ft_substr(str, 0, i);
				prev = ft_strjoin_2(prev, ft_strdup(" "));
				next = ft_substr(str, i, ft_strlen(str) - i);
				free (str);
				str = ft_strjoin_2(prev, next);	
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