/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/04 14:00:00 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	ft_init(&data, env);
	while (1)
	{
		data.error = 0;
		ft_get_input(&data);
		if (data.history && ft_strlen(data.history) > 0)
			add_history(data.history);
		ft_clear_history(&data);
		ft_clear_input(&data);
	}
	return (0);
}
