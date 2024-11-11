/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/11 15:32:47 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_restart(void)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	waiting_signal(&data);
	ft_init(&data, env);
	data.error = 0;
	while (1)
	{
		ft_get_input(&data);
		if (data.history && ft_strlen(data.history) > 0)
			add_history(data.history);
		ft_clear_history(&data);
		ft_clear_input(&data);
		data.error = 0;
	}
	return (0);
}
