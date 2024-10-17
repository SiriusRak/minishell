/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:09:48 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/17 07:41:15 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_init(t_data *data, char **env)
{
    char    *path;
    int     i;

    i = 0;
    path = NULL;
    data->list = NULL;
    data->input = NULL;
    data->prompt = NULL;
    data->history = NULL;
    data->path = ft_split(getenv("PATH"), ":");
    path = ft_strdup(env[i]);
    i++;
    while (env[i])
    {
        path = ft_strjoin_2(path, ft_strdup("\n"));
        path = ft_strjoin_2(path, ft_strdup(env[i]));
        i++;
    }
    data->env = ft_split(path, "\n=");
    free (path);
}
