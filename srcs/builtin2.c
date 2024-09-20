/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:41:09 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/20 13:41:33 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_add_new_var(char *key, t_data *data, char *arg, char *new_var)
{
    char    **new_env;
    int     i;
    int     len_env;

    i = 0;
    len_env = ft_count_line(data->env);
    new_env = malloc(sizeof(char *) * (len_env + 2));
    while (i < ft_count_line(data->env))
    {
        new_env[i] = ft_strdup(data->env[i]);
        i++;
    }
    new_env[i] = ft_strdup(new_var);
    new_env[++i] = 0;
    data->env = new_env;
    free(new_var);
    // ft_free_split(new_env, len_env + 1);
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
    ft_strlcpy(new_var, key, ft_strlen(key) + 1);
    ft_strlcat(new_var, args, ft_strlen(args) + ft_strlen(new_var) + 1);
    while (data->env[i])
    {
        if (strncmp(data->env[i], key, ft_strlen(key)) == 0)
        {
            data->env[i] = ft_strdup(new_var);
            free(new_var);
            return ;
        }
        i++;
    }
    ft_add_new_var(key, data, args, new_var);
}
