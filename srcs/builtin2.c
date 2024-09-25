/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:41:09 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/25 14:55:32 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_builtin_export(char *key, t_data *data, char *args)
{
	t_list	*tmp;
	int		is_exist;

	tmp = data->env;
	is_exist = 1;
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
