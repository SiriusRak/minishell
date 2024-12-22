/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:15:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/19 17:50:57 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <time.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}

void	ft_lstclear_2(t_list **list)
{
	t_list	*temp;

	if (*list)
	{
		while (*list)
		{
			temp = (*list)->next;
			if ((*list)->content)
			{
				free((*list)->content);
				(*list)->content = NULL;
			}
			free(*list);
			*list = temp;
		}
	}
}
