/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:42:56 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/12 09:20:54 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	ft_pars(t_d_list *list, char *script)
// {
// 	int     i;
// 	int		start;

// 	i = 0;
// 	while (script[i])
// 	{
// 		if (script[i] == '\'' || script[i] == '\"')
// 		{
// 			if (script[i] == '\'')
// 			{

// 			}
// 		}
// 	}
	

// }

int	ft_check_list(t_data *data)
{
	t_d_list	*list;

	list = data->list;
	while (list)
	{
		list->token->name = ft_epure_line(list->token->name);
		ft_epure_redir(list->token->name);
		// if (!ft_pars(list))
		// 	return (0);
		list = list->next;
	}
	return (1);
}
