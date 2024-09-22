/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/22 16:40:01 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_init(char **env, t_data *data)
{
	char	*path;

	path = getenv("PATH");
	data->env = ft_split(path, ":");
	data->sep = malloc(sizeof(char) * 6);
	data->sep = " \'\"$<>|";
	data->list = NULL;
	return (0);
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
