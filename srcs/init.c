/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:09:48 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/04 14:07:19 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <time.h>

void	ft_init(t_data *data, char **env)
{
	data->list = NULL;
	data->temp_list = NULL;
	data->input = NULL;
	data->prompt = NULL;
	data->history = NULL;
	data->return_value = 0;
	data->pid = 3020814;
	data->signal = malloc(sizeof(t_signal) * 1);
	data->env = ft_duplicate(env);
	data->saved_fd = -1;
	data->path = 1;
}
