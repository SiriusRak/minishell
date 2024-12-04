/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epure2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:28:22 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/30 17:29:51 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
