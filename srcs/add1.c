/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:43:44 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/20 20:34:14 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <time.h>

int	ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	fork_heredoc(t_d_list *list, char *str, char c)
{
	char	**tab;
	char	*here;
	int		i;

	waiting_signial_here(list->data);
	here = ft_add_heredoc(list, str, c);
	ft_add_file(here, str);
	list->data->history = ft_strjoin_2(list->data->history, here);
	ft_clear_heredoc(list->data);
	ft_clear_input(list->data);
	tab = list->data->tab;
	i = list->data->i;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	ft_exit_child(list->data, 0);
}

int	ft_add_in(t_d_list *list, char *str, int i)
{
	t_list	*lst;
	int		c;

	if (!ft_check_error(str))
		return (1);
	c = ft_check_quote(str);
	str = ft_clean_quote(list, str, i);
	if (i == HERE)
	{
		signal(SIGINT, SIG_IGN);
		list->data->is_heredoc = 1;
		list->data->signal->pid = fork();
		if (list->data->signal->pid == 0)
			fork_heredoc(list, str, c);
	}
	lst = ft_lstnew(str);
	lst->type = i;
	ft_lstadd_back(&(list->token->in), lst);
	return (0);
}

int	ft_add_cmd(t_d_list *list, char *str)
{
	t_list	*lst;

	str = ft_clean_quote(list, str, 0);
	lst = ft_lstnew(str);
	if (!list->token->cmd)
		lst->type = CMD;
	else
		lst->type = ARG;
	ft_lstadd_back(&(list->token->cmd), lst);
	return (0);
}
