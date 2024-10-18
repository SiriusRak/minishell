/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 07:13:03 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/15 14:04:47 by enarindr         ###   ########.fr       */
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
		if (list->type == CMD)
			name = "CMD";
		else if (list->type == ARG)
			name = "ARG";
		else if (list->type == HERE)
			name = "HEREDOC";
		else if (list->type == IN)
			name = "INPUT";
		else if (list->type == OUT)
			name = "OUT";
		else if (list->type == OUT_2)
			name = "OUT_2";
		printf("--------%s[%d]--------\n", name, i);
		printf("%s\n", list->content);
		list = list->next;
		i++;
	}
	return (0);
}

int		ft_print_all(t_data *data)
{
	t_d_list	*list;
	int			pipe;

	list = data->list;
	pipe = 0;
	printf("---------------------------------\n");
	while (list)
	{
		if (list->token->name)
			printf("prompt[%d] : %s\n", pipe, list->token->name);
		printf("\n");
		if (list->token->cmd)
			print_child(&(list->token->cmd));
		if (list->token->in)
			print_child(&(list->token->in));
		if (list->token->out)
			print_child(&(list->token->out));
		printf("\n");
		list = list->next;
		pipe++;
	}
	printf("---------------------------------\n");
	return (0);
}