/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:46:17 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/07 08:36:06 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_exit(t_data *data, int i)
{
	int a;

	a = 0;
	while ((data->env)[a])
	{
		free ((data->env)[a]);
		a++;
	}
	if (i == 2)
		free (data->input);
	free (data->env);
	if (i == 1)
		ft_free_loop(data, i);
	if (data->prompt)
		free (data->prompt);
	exit (0);
	return (0);
}
