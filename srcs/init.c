/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:26:35 by enarindr          #+#    #+#             */
/*   Updated: 2024/09/28 14:27:33 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_init_list(t_d_list **list)
{
	(*list)->token->arg = NULL;
	(*list)->token->cmd = NULL;
	(*list)->token->in = NULL;
	(*list)->token->out = NULL;
	(*list)->token->var = NULL;
	(*list)->token->var_two = NULL;
	(*list)->token->heredoc = NULL;
}

int	ft_init(char **env, t_data *data)
{
	(void) env;
	data->env = ft_split(getenv("PATH"), ":");
	data->input = NULL;
	data->list = NULL;

	return (0);
}