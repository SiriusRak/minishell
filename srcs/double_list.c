/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:19:47 by enarindr          #+#    #+#             */
/*   Updated: 2024/11/30 17:27:40 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <time.h>

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

t_d_list	*ft_newlist(char *content, t_data *data)
{
	t_d_list	*new;
	t_token		*token;

	new = (t_d_list *) malloc(sizeof(t_d_list));
	token = (t_token *) malloc(sizeof(t_token));
	if (!new || !token)
		return (NULL);
	new->token = token;
	new->data = data;
	new->token->name = content;
	new->token->path = NULL;
	new->token->cmd = NULL;
	new->token->in = NULL;
	new->token->out = NULL;
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

int	ft_add_list(t_data *data, int start, int i, char *str)
{
	char	*content;

	content = ft_substr(str, start, i - start);
	ft_add_back_list(&(data->temp_list), ft_newlist(content, data));
	return (i);
}
