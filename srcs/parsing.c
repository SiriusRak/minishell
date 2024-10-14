/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:42:56 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/14 17:22:47 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*lexer(char *script, int i)
// {
// 	char	*token;
// 	int		len;

// 	i++;
// 	while (ft_notsep(script[i]))
// 	{
// 		/* code */
// 	}
	
// }

// int	ft_pars(t_d_list *list)
// {
// 	int     i;
// 	char	*script;
// 	char	*token;

// 	script = list->token->name;
// 	i = 0;
// 	while (script[i])
// 	{
// 		if (script[i] == '\'' || script[i] == '\"')
// 		{
// 			if (script[i] == '\'')
// 				i = ft_find_next_quote_2(script, i, 1);
// 			else if (script[i] == '\"')
// 				i = ft_find_next_quote_2(script, i, 2);
// 		}
// 		token = ft_lexer(script, i);
// 		if (!token)
// 			return (NULL);
// 		ft_add_type(list, token);
// 		i += ft_strlen(token), 
// 	}
// }


int		ft_invalid_redir(char *str)
{
	int		i;
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
					return (1);
			}
			i++;
			if (str[i] != ' ' && str[i] != c)
			{
				printf ("ato----\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*ft_arrange_redir(char *str)
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
					return (str);
				}
			}
			i++;
			if (str[i] != ' ' && str[i] != c)
			{
				prev = ft_substr(str, 0, i);
				prev = ft_strjoin_2(prev, ft_strdup(" "));
				next = ft_substr(str, i, ft_strlen(str) - i);
				printf("ato\n");
				free (str);
				str = ft_strjoin_2(prev, next);
				return (str);
			}
		}
		i++;
	}
	return (str);
}

char	*ft_epure_redir(char *str)
{
	char	*new;

	new = ft_strdup(str);
	while (ft_invalid_redir(new))
		new = ft_arrange_redir(new);
	free (str);
	return (new);	
}

int	ft_check_list(t_data *data)
{
	t_d_list	*list;

	list = data->list;
	while (list)
	{
		list->token->name = ft_epure_line(list->token->name);
		list->token->name =  ft_epure_space(list->token->name);
		list->token->name = ft_epure_redir(list->token->name);
		// if (!ft_pars(list))
		// 	return (0);
		list = list->next;
	}
	return (1);
}
