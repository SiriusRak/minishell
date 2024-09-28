/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 09:14:55 by enarindr          #+#    #+#             */
/*   Updated: 2024/09/28 13:50:22 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_t_free_list(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free (*list);
		*list = temp;
	}
	return (0);
}

int	ft_d_free_list(t_d_list **list)
{
	t_d_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		ft_t_free_list(&(*list)->token->arg);
		ft_t_free_list(&(*list)->token->cmd);
		ft_t_free_list(&(*list)->token->heredoc);
		ft_t_free_list(&(*list)->token->in);
		ft_t_free_list(&(*list)->token->out);
		ft_t_free_list(&(*list)->token->var);
		ft_t_free_list(&(*list)->token->var_two);
		free ((*list)->token->name);
		free ((*list)->token);
		free (*list);
		*list = temp;
	}
	return (0);
}

int    ft_free_loop(t_data *data, int i)
{
	if (i == 1)
		free (data->input);
	ft_d_free_list (&(data->list));
	return (0);
}