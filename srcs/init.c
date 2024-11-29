/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:09:48 by enarindr          #+#    #+#             */
/*   Updated: 2024/11/29 10:41:37 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <time.h>

void    ft_init(t_data *data, char **env)
{
    data->list = NULL;
    data->temp_list = NULL;
    data->input = NULL;
    data->prompt = NULL;
    data->history = NULL;
    data->pid = 3020814;
    data->path = ft_split(getenv("PATH"), ":");
    data->signal = malloc(sizeof(t_signal) * 1);
    data->env = ft_duplicate(env);
    data->saved_fd = -1;
}
