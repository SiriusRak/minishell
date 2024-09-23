/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/23 16:36:12 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init(char **env, t_data *data)
{
	char *path;

	data->env = ft_dup(env);
	data->list = malloc(sizeof(t_d_list));
	data->list->token = malloc(sizeof(t_token));
	data->list->token->out = NULL;
	ft_lstadd_back(&(data->list->token->out), ft_lstnew("test.txt"));
	ft_lstadd_back(&data->list->token->out, ft_lstnew("test1.txt"));
	ft_lstadd_back(&data->list->token->out, ft_lstnew("test2.txt"));
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	waiting_signal();
	ft_init(env, &data);
	while(1)
	{
		get_input(&data);
	}
}
