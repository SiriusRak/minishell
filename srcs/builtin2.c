/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:41:09 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/24 13:57:55 by enarindr         ###   ########.fr       */
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

void	ft_builtin_export(char **keys, t_data *data, char **args)
{
	t_list	*tmp;

	tmp = data->env;
	if (!args[0])
	{
		ft_export_no_arg(data);
		return ;
	}
	while (data->env)
	{
		ft_key_isexist(data->env, keys, args);
		if (!data->env->next)
			break;
		data->env = data->env->next;
	}
	data->env = tmp;
	ft_addkey(data->env, keys, args);
}
//taf: invalid read of size/unset path
void	ft_builtin_unset(t_data *data, char **key)
{
	t_list	*head;
	t_list	*prev;
	int		i;

	head = data->env;
	prev = NULL;
	while (data->env)
	{
		i = 0;
		while (i < ft_count_line(key))
		{
			if (!ft_strncmp(data->env->content, key[i], ft_strlen(key[i])))
			{
				if (prev == NULL)
					data->env = data->env->next;
				else
					prev->next = data->env->next;
				free(data->env->content);
				break;
			}
			i++;
		}	
		prev = data->env;
		data->env = data->env->next;
	}
	data->env = head;
}
void	ft_execute_builtin(t_data *data, char *cmd)
{
	int		len;
	char	**keys;
	char	**arg;

	arg = ft_lst_to_char(data->list->token->cmd, 1);
	keys = ft_get_allkey(data->list->token->cmd);
	len = ft_strlen(cmd);
	if (data->list->token->out != NULL)
			ft_redir(data, data->list->token->out);
	if (data->list->token->in != NULL)
			ft_redir_input(data->list->token->in);
	if (!ft_strncmp(cmd, "echo", len))
		ft_builtin_echo(arg);
	else if (!ft_strncmp(cmd, "exit", len))
		ft_builtin_exit(arg);
	else if (!ft_strncmp(cmd, "env", len))
		ft_builtin_env(data);
	else if (!ft_strncmp(cmd, "export", len))
		ft_builtin_export(keys, data, arg);
	else if (!ft_strncmp(cmd, "unset", len))
		ft_builtin_unset(data, arg);
	else if (!ft_strncmp(cmd, "cd", len))
		ft_buitlin_cd(arg, data);
	else if (!ft_strncmp(cmd, "pwd", len))
		ft_builtin_pwd();
	if (data->saved_fd >= 0)
		ft_restore_fd(data->saved_fd);
	ft_free_split(arg);
	ft_free_split(keys);
}
