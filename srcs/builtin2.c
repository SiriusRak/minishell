/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:41:09 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/19 17:09:51 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_add_new_var(char *key, t_data *data, char *arg, char *new_var)
{
    char    **new_env;
    int     i;

    i = 0;
    new_env = malloc(sizeof(char *) * ft_count_line(data->env) + 2);
    while (i < ft_count_line(data->env))
    {
        new_env[i] = ft_strdup(data->env[i]);
        i++;
    }
    new_env[i] = new_var;
    new_env[++i] = 0;
    ft_free_split(data->env, ft_count_line(data->env));
    data->env = new_env;
    ft_free_split(new_env, i);
}

void    ft_builtin_export(char *key, t_data *data, char *args)
{
    char    *new_var;
    // char    *arg;
    int     i;

    i = 0;
    // arg = data->list->token->arg;
    new_var = malloc(ft_strlen(key) + ft_strlen(args) + 1);
    if (!new_var)
        return ;
    ft_strlcpy(new_var, key, ft_strlen(key));
    ft_strlcat(new_var, args, ft_strlen(args) + ft_strlen(new_var));
    while (data->env[i])
    {
        if (strncmp(data->env[i], key, ft_strlen(key)) == 0)
        {
            free(data->env[i]);
            data->env[i] = new_var;
            return ;
        }
        i++;
    }
    ft_add_new_var(key, data, args, new_var);
}
