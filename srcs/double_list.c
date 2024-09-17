/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:19:47 by enarindr          #+#    #+#             */
/*   Updated: 2024/09/17 07:13:57 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstfree(t_d_list **list)
{
	t_d_list	*temp;

	if (list)
	{
		while (*list)
		{
			temp = (*list)->next;
			free(*list);
			(*list) = temp;
		}
	}
	return (0);
}

t_d_list	*ft_newlist(char *content)
{
	t_d_list	*new;

	new = (t_d_list *) malloc(sizeof(t_d_list));
	if (!new)
		return (NULL);
	new->token->name = content;
	new->token->arg = 0;
	new->token->cmd = 0;
	new->token->pip = 0;
	new->token->redir = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add_front_list(t_d_list **list, t_d_list *new)
{
	t_d_list	*temp;

	if (list && new)
	{
		if (*list == NULL)
			*list = new;
		temp = *list;
		temp->prev = new;
		new->next = temp;
		list = &new;
	}
}

void	ft_add_back_list(t_d_list **list, t_d_list *new)
{
	t_d_list	*temp;

	if (list && new)
	{
		if (*list == NULL)
			*list = new;
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}