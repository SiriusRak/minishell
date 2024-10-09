/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/09 07:55:20 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_convert_list(t_data *data)
{
	char		**tab;
	t_d_list	*list;
	int			i;

	tab = ft_split(data->input, "|");
	data->tab = tab;
	i = 0;
	list = NULL;
	while (tab[i])
	{
		ft_add_back_list(&(list), ft_newlist(tab[i]));
		i++;
	}
	data->pipe = i;
	data->list = list;
}

int	ft_tokenisation(t_data *data)
{
	t_d_list	*temp;

	ft_convert_list(data);
	temp = *(&(data->list));
	while (temp)
	{
		ft_init_list(&(temp));
		temp->data = data;
		if (ft_is_heredoc(temp->token->name))
			ft_heredoc(temp);
		temp = temp->next;
	}
	free (data->tab);
	data->prompt = ft_strjoin_2(data->prompt, ft_strdup(data->input));
	free (data->input);
	data->input = NULL;
	return (0);
}

void	ft_echange_list(t_data *data)
{
	t_d_list	*temp;

	temp = data->list;
	data->list = NULL;
	ft_add_back_list(&(data->final_list), temp);
}

int	get_input(t_data *data)
{
	char		*rd_line;

	rd_line = readline("😂😂😂😂$ ");
	if (!rd_line)
		return (1);
	data->input = ft_epure_line(rd_line);
	free (rd_line);
	if (ft_strncmp(data->input, "exit", 4) == 0)
		ft_exit (data, 2);
	ft_tokenisation(data);
	ft_echange_list(data);
	while (ft_end_pip(data->prompt))
	{

		rd_line = readline("🥶🥶$ ");
		if (!rd_line)
			return (1);
		data->input = ft_epure_line(rd_line);
		ft_tokenisation(data);
		ft_echange_list(data);
	}
	printf("[--prompt%s--]\n", data->prompt);
	ft_print_all(data);
	add_history(data->prompt);
	return (0);
}
