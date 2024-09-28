/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:26:35 by enarindr          #+#    #+#             */
/*   Updated: 2024/09/28 08:22:29 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_init_list(t_d_list **list)
{
	t_d_list 	*temp;

	temp = *list;
	while (temp)
	{
		temp->token->arg = NULL;
		temp->token->cmd = NULL;
		temp->token->in = NULL;
		temp->token->out = NULL;
		temp->token->var = NULL;
		temp->token->var_two = NULL;
		temp->token->heredoc = NULL;
		temp = temp->next;
	}
}

int	ft_init(char **env, t_data *data)
{
	(void) env;
	data->env = ft_split(getenv("PATH"), ":");
	data->sep = ft_strdup(" ;\'\"$<>|");
	data->input = NULL;
	data->list = NULL;

	return (0);
}