/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:42:56 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/14 20:55:17 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pars(t_d_list *list)
{
	int		i;
	int		j;
	char	*str;
	char	*token;

	i = 0;
	str = list->token->name;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			j = i;
			if (str[i] == '\'')
				i = ft_find_next_quote_2(str, i, 1);
			else if (str[i] == '\"')
				i = ft_find_next_quote_2(str, i, 2);
			token = ft_substr(str, j, i - j + 1);
			ft_add_type(token, list)
		}
		if(str[i] == '<' || str[i] == '>')
		{
			j = i;
			while (str[i] != ' ')
				i++;
			while (str[i] != ' ')
				i++;
			token = ft_substr(str, j, i - j + 1);
			ft_add_type(token, list);
		}
	}
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
		if (!ft_pars(list))
			return (0);
		list = list->next;
	}
	return (1);
}
