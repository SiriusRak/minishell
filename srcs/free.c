/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:35:15 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/20 21:03:37 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <time.h>

int	ft_clear_heredoc(t_data *data)
{
	t_list	*heredoc;

	if (data->list)
	{
		if (data->list->token)
		{
			if (data->list->token->in)
			{
				heredoc = data->list->token->in;
				while (heredoc)
				{
					if (heredoc->type == HERE)
						unlink(heredoc->content);
					heredoc = heredoc->next;
				}
			}
		}
	}
	return (0);
}

int	ft_clear_history(t_data *data)
{
	ft_clear_heredoc(data);
	ft_free_data(data);
	return (0);
}

int	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free (tab);
		tab = NULL;
	}
	return (0);
}

int	ft_free_data(t_data *data)
{
	if (data->input)
		free(data->input);
	data->input = NULL;
	if (data->history)
	{
		free (data->history);
		data->history = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->list)
	{
		ft_free_t_d_list(data->list);
		data->list = NULL;
		data->temp_list = NULL;
	}
	if (data->keys)
		ft_free_split(data->keys);
	data->keys = NULL;
	return (0);
}

int	ft_free_t_d_list(t_d_list *lst)
{
	t_d_list	*list;
	t_d_list	*temp;

	list = lst;
	while (list)
	{
		temp = list->next;
		if (list->token)
		{
			if (list->token->cmd)
				ft_lstclear_2(&(list->token->cmd));
			if (list->token->in)
				ft_lstclear_2(&(list->token->in));
			if (list->token->out)
				ft_lstclear_2(&(list->token->out));
			if (list->token->name)
				free (list->token->name);
			if (list->token->path)
				free (list->token->path);
			free(list->token);
		}
		free (list);
		list = temp;
	}
	return (0);
}
