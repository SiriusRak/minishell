/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/25 17:19:43 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_list(t_data *data)
{
	data->input = NULL;
	data->list->token->arg = NULL;
	data->list->token->cmd = NULL;
	data->list->token->heredoc = NULL;
	data->list->token->in = NULL;
	data->list->token->out = NULL;
	data->list->token->var = NULL;
}

int	ft_init(char **env, t_data *data)
{
	data->env = ft_split(getenv("PATH"), ":");
	data->sep = ft_strdup(" ;\'\"$<>|\0");
	data->list = malloc(sizeof (t_d_list));
	data->list->token = malloc(sizeof(t_token));
	// data->list->token->heredoc = malloc(sizeof(t_list));
	ft_init_list(data);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	waiting_signal();
	ft_init(env, &data);
	while(get_input(&data) == 0)
		free (data.input);
}
