/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:41:09 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/20 16:46:07 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_remove_line(t_data *data)
{
    int     i;
    int     len;
    char    **new_env;

    i = 0;
    len = ft_count_line(data->env);
    new_env = malloc(sizeof(char *) * len);
    while (i < len - 1)
    {
        new_env[i] = ft_strdup(data->env[i]);
        i++;
    }
    new_env[i] = 0;
    ft_free_split(data->env);
    data->env = ft_dup(new_env);
    ft_free_split(new_env);
}

void    ft_add_new_var(char *key, t_data *data, char *arg, char *new_var)
{
    char    **new_env;
    int     i;
    int     len_env;

    i = 0;
    len_env = ft_count_line(data->env);
    new_env = malloc(sizeof(char *) * (len_env + 2));
    while (data->env[i])
    {
        new_env[i] = ft_strdup(data->env[i]);
        i++;
    }
    new_env[i] = ft_strdup(new_var);
    new_env[++i] = 0;
    ft_free_split(data->env);
    data->env =  ft_dup(new_env);
    free(new_var);
    ft_free_split(new_env);
}

void    ft_builtin_export(char *key, t_data *data, char *args)
{
    char    *new_var;
    // char    *arg;
    int     i;
    int     is_exist;

    i = 0;
    is_exist = 0;
    // arg = data->list->token->arg;
    new_var = malloc(ft_strlen(key) + ft_strlen(args) + 1);
    if (!new_var)
        return ;
    ft_strlcpy(new_var, key, ft_strlen(key) + 1);
    ft_strlcat(new_var, args, ft_strlen(args) + ft_strlen(new_var) + 1);
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], key, ft_strlen(key)) == 0)
        {
            free(data->env[i]);
            data->env[i] = ft_strdup(new_var);
            free(new_var);
            is_exist = 1;
        }
        i++;
    }
    if (!is_exist)
        ft_add_new_var(key, data, args, new_var);
}
void    ft_builtin_unset(t_data *data, char *key)
{
    int i;
    int j;
    int len;

    i = 0;
    len = ft_strlen(key);
    while (data->env[i])
    {
        if (strncmp(key, data->env[i], len) == 0 && data->env[i][len] == '=')
        {
            j = i;

            while (j < ft_count_line(data->env) - 1)
            {
                free(data->env[j]);
                data->env[j] = ft_strdup(data->env[j + 1]);
                j++;
            }
            ft_remove_line(data);
        }
        i++;
    }
}
