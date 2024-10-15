/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/15 17:19:05 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data	data;

	waiting_signal();
	ft_init(&data);
	while (ft_get_input(&data))
	{
		if (data.history && ft_strlen(data.history) > 0)
			add_history(data.history);
		ft_clear_history(&data);
		ft_clear_input(&data);
	}
	return (0);
}
