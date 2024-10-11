/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:35:15 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/11 16:20:48 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_clear_history(t_data *data)
{
	add_history(data->history);
	ft_free_data(data);
	rl_on_new_line();
	rl_replace_line("", 0);
	return (0);
}

int ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free (tab);
	return (0);
}

int	ft_free_data(t_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
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
		ft_free_t_d_list(data);
		data->list = NULL;
	}
	return (0);
}

int	ft_free_t_d_list(t_data *data)
{
	t_d_list	*list;
	t_d_list	*temp;

	list = data->list;
	while (list)
	{
		temp = list->next;
		if (list->token)
		{
			if (list->token->cmd)
				ft_lstclear_2(&(list->token->cmd));
			if (list->token->heredoc)
				ft_lstclear_2(&(list->token->heredoc));
			if (list->token->in)
				ft_lstclear_2(&(list->token->in));
			if (list->token->out)
				ft_lstclear_2(&(list->token->out));
			if (list->token->name)
				free (list->token->name);
			free(list->token);
		}
		free (list);
		list = temp;
	}
	return (0);
}
