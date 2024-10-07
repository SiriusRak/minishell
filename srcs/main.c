/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/07 16:34:33 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init(char **env, t_data *data)
{
	data->env = ft_duplicate(env);
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
