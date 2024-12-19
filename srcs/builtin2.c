/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:41:09 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/19 15:49:08 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_no_arg(t_data *data)
{
	char	**env;
	int		i;

	env = ft_lst_to_char(data->env, 0);
	env = ft_sort_tab(env);
	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	ft_free_split(env);
}

int	ft_builtin_export(t_data *data, char **args)
{
	t_list	*tmp;

	tmp = data->env;
	if (data->keys == NULL)
		data->keys = ft_get_allkey(data->list->token->cmd);
	if (!args[0] || args[0][0] == ' ' || args[0][0] == '\0')
	{
		ft_export_no_arg(data);
		return (0);
	}
	while (data->env)
	{
		ft_key_isexist(data->env, data->keys, args);
		if (!data->env->next)
			break ;
		data->env = data->env->next;
	}
	data->env = tmp;
	ft_addkey(data->env, data->keys, args);
	if (!ft_check_allkey(data->keys))
		return (1);
	return (0);
}

int	ft_builtin_unset(t_data *data, char **key)
{
	t_list	*curr;
	t_list	*prev;
	int		i;

	i = 0;
	while (i < ft_count_line(key))
	{
		curr = data->env;
		prev = NULL;
		while (curr)
		{
			if (ft_manage_unset(key[i], curr, prev, data))
				break ;
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}

void	ft_execute_builtin(t_data *data, char *cmd)
{
	int		len;
	char	**arg;

	arg = ft_lst_to_char(data->list->token->cmd, 1);
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len) && len == 4)
		data->return_value = ft_builtin_echo(arg, data);
	else if (!ft_strncmp(cmd, "exit", len) && len == 4)
		data->return_value = ft_builtin_exit(data, arg);
	else if (!ft_strncmp(cmd, "env", len) && len == 3)
		data->return_value = ft_builtin_env(data);
	else if (!ft_strncmp(cmd, "export", len) && len == 6)
		data->return_value = ft_builtin_export(data, arg);
	else if (!ft_strncmp(cmd, "unset", len) && len == 5)
		data->return_value = ft_builtin_unset(data, arg);
	else if (!ft_strncmp(cmd, "cd", len) && len == 2)
		data->return_value = ft_buitlin_cd(arg, data);
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
		data->return_value = ft_builtin_pwd();
	if (data->saved_fd >= 0)
		ft_restore_fd(data, data->saved_fd);
	ft_free_split(arg);
}
