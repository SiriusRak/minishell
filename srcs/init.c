/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:09:48 by enarindr          #+#    #+#             */
/*   Updated: 2024/11/11 09:17:12 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <time.h>

void    ft_init(t_data *data, char **env)
{
    data->list = NULL;
    data->temp_list = NULL;
    data->input = NULL;
    data->prompt = NULL;
    data->history = NULL;
    data->path = ft_split(getenv("PATH"), ":");
    data->signal = malloc(sizeof(t_signal) * 1);
    data->env = ft_duplicate(env);
    data->old_pwd = getenv("OLDPWD");
    data->pwd = getenv("PWD");
    data->saved_fd = -1;
}
