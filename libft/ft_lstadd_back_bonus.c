/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:09:03 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/03 16:34:07 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

t_list	*ft_add_node(t_list *head, char *str)
{
	t_list	*new_node;
	t_list	*tmp;

	tmp = head;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(str);
	new_node->next = NULL;
	if (!head)
		return (new_node);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}
