/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:09:48 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/20 20:33:46 by enarindr         ###   ########.fr       */
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
	data->keys = NULL;
	data->heredoc = NULL;
	data->tab = NULL;
	data->checker = NULL;
}
