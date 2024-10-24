/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/24 13:22:19 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data	data;

	waiting_signal(&data);
	ft_init(&data, env);
	data.error = 0;
	while (ft_get_input(&data))
	{
		if (data.history && ft_strlen(data.history) > 0)
			add_history(data.history);
		ft_clear_history(&data);
		ft_clear_input(&data);
		data.error = 0;
	}
	return (0);
}
