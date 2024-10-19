/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:09:48 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/19 11:11:50 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_init(t_data *data, char **env)
{
    data->list = NULL;
    data->input = NULL;
    data->prompt = NULL;
    data->history = NULL;
    data->path = ft_split(getenv("PATH"), ":");
    data->env = ft_duplicate(env);
    data->old_pwd = getenv("OLDPWD");
    data->pwd = getenv("PWD");
}
