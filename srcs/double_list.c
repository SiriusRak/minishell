/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circulaire_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:19:47 by enarindr          #+#    #+#             */
/*   Updated: 2024/08/08 11:13:01 by enarindr         ###   ########.fr       */
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
}

t_d_list	*ft_newlist(long *content)
{
	t_d_list	*new;

	new = (t_d_list *) malloc(sizeof(t_d_list));
	if (!new)
		return (NULL);
	new->content = content;
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
