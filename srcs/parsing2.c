/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:18:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/20 19:44:18 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_clean_list(t_d_list *list)
{
	list->token->name = ft_epure_line(list->token->name, 0, 0);
	list->token->name = ft_epure_space(list->token->name, 0, 0);
	list->token->name = ft_epure_redir(list->token->name);
	return (0);
}

int	ft_check_list_ext(t_data *data)
{
	if (data->is_heredoc)
	{
		check_after_child(data);
		if (ft_chek_sig(data))
		{
			if (data->temp_list)
				ft_free_t_d_list(data->temp_list);
			data->temp_list = NULL;
			return (0);
		}
	}
	return (1);
}

int	ft_check_list(t_data *data)
{
	t_d_list	*list;

	list = data->temp_list;
	while (list)
	{
		data->is_heredoc = 0;
		ft_clean_list(list);
		if (!ft_pars(list))
		{
			ft_free_t_d_list(data->temp_list);
			data->temp_list = NULL;
			if (!ft_check_list_ext(data))
				return (0);
			return (0);
		}
		if (!ft_check_list_ext(data))
			return (0);
		list = list->next;
	}
	return (1);
}

int	ft_lex_ext2(t_d_list *list, char **tab, int i)
{
	int	error;

	error = 0;
	if (tab[i][0] == '>' && ft_strlen(tab[i]) == 1)
		error = ft_add_out(list, tab[i + 1], OUT);
	else if (tab[i][0] == '>' && tab[i][1] == '>')
		error = ft_add_out(list, tab[i + 1], OUT_2);
	else if (tab[i][0] == '<' && ft_strlen(tab[i]) == 1)
		error = ft_add_in(list, tab[i + 1], IN);
	else if (tab[i][0] == '<' && tab[i][1] == '<')
	{
		list->data->tab = tab;
		list->data->i = i;
		error = ft_add_in(list, tab[i + 1], HERE);
	}
	return (error);
}
