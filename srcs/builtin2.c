/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:41:09 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/07 12:47:35 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_no_arg(t_data *data)
{
	char	**env;
	int		i;

	env = ft_lstcopy(data->env);
	ft_sort_tab(env);
	i = 0;
	while (env[i])
	{
		printf("export %s\n", env[i]);
		i++;
	}
}
//TAF: export avec variable sans valeur
void	ft_builtin_export(char *key, t_data *data, char *args)
{
	t_list	*tmp;
	int		is_exist;

	tmp = data->env;
	is_exist = 1;
	if (!args)
	{
		ft_export_no_arg(data);
		return ;
	}
	while (data->env && is_exist)
	{
		if (ft_strncmp(data->env->content, key, ft_strlen(key)) == 0)
		{
			free(data->env->content);
			data->env->content = ft_strdup(args);
			is_exist = 0;
		}
		if (!data->env->next)
			break;
		data->env = data->env->next;
	}
	if (is_exist)
		data->env = ft_add_node(data->env, args);
	data->env = tmp;
}

void	ft_builtin_unset(t_data *data, char *key)
{
	t_list	*head;
	t_list	*prev;
	size_t	len;

	len = ft_strlen(key);
	head = data->env;
	prev = NULL;
	while (data->env)
	{
		if (!ft_strncmp(data->env->content, key, len))
		{
			if (prev == NULL)
				data->env = data->env->next;
			else
				prev->next = data->env->next;
			free(data->env->content);
			break;
		}
		prev = data->env;
		data->env = data->env->next;
	}
	data->env = head;
}
void	ft_execute_builtin(t_data *data, char *cmd, char *arg)
{
	int	len;
	char *key;

	key = ft_get_key(data->list->token->arg);
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		ft_builtin_echo(arg);
	else if (!ft_strncmp(cmd, "exit", len))
		ft_builtin_exit(arg);
	else if (!ft_strncmp(cmd, "env", len))
		ft_builtin_env(data);
	else if (!ft_strncmp(cmd, "export", len))
		ft_builtin_export(key, data, arg);
	else if (!ft_strncmp(cmd, "unset", len))
		ft_builtin_unset(data, arg);
	else if (!ft_strncmp(cmd, "cd", len))
		ft_buitlin_cd(arg);
	else if (!ft_strncmp(cmd, "pwd", len))
		ft_builtin_pwd();
}
