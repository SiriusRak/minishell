/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/18 10:19:25 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	waiting_signal();
	ft_init(&data, env);
	while (ft_get_input(&data))
	{
		if (data.history && ft_strlen(data.history) > 0)
			add_history(data.history);
		// ft_execute();
		ft_clear_history(&data);
		ft_clear_input(&data);
	}
	return (0);
}
