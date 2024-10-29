/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/24 20:37:02 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	int		return_value;
	t_data	data;

	(void)ac;
	(void)av;
	waiting_signal(&data);
	ft_init(&data, env);
	data.error = 0;
	return_value = 0;
	while (1)
	{
		return_value = ft_get_input(&data);
		data.return_value = return_value;
		if (data.history && ft_strlen(data.history) > 0)
			add_history(data.history);
		ft_clear_history(&data);
		ft_clear_input(&data);
		data.error = 0;
	}
	return (0);
}
