/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 07:13:03 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/09 08:18:42 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		print_child(t_list **lst)
{
	t_list	*list;
	char	*name;
	int		i;

	list = *lst;
	i = 0;
	while (list)
	{
		printf("%s[%d]\n", name, i);
		list = list->next;
		i++;
	}
	return (0);
}

int		ft_print_all(t_data *data)
{
	t_d_list	*list;
	int			pipe;

	list = data->final_list;
	pipe = 0;
	printf("---------------------------------\n");
	printf("[--prompt:  %s--]\n", data->prompt);
	while (list)
	{
		printf("pipe--[%d]\n", pipe);
		if (list->token->name)
			printf("commande[%d]\n", pipe);
		if (list->token->arg)
			print_child(&(list->token->arg));
		if (list->token->cmd)
			print_child(&(list->token->cmd));
		if (list->token->heredoc)
			print_child(&(list->token->heredoc));
		if (list->token->in)
			print_child(&(list->token->in));
		if (list->token->out)
			print_child(&(list->token->out));
		list = list->next;
		pipe++;
	}
	printf("---------------------------------\n");
	return (0);
}