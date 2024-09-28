/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:19:47 by enarindr          #+#    #+#             */
/*   Updated: 2024/09/28 06:47:46 by enarindr         ###   ########.fr       */
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
	t_token		*token;

	new = (t_d_list *) malloc(sizeof(t_d_list));
	token = (t_token *) malloc(sizeof(t_token));
	if (!new || !token)
		return (NULL);
	new->token = token;
	new->token->name = content;
	new->token->arg = NULL;
	new->token->cmd = NULL;
	new->token->in = NULL;
	new->token->out = NULL;
	new->token->var = NULL;
	new->token->heredoc = NULL;
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

	if (*list == NULL)
		*list = new;
	else 
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}
