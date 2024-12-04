/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:48:21 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/04 16:14:10 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_key(char *key)
{
	int	i;

	i = 0;
	if (key[0] == '-' && ft_strlen(key) > 2)
		return (-1);
	if (key[0] != '_' && !isalpha(key[i]))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_allkey(char **keys)
{
	int	i;

	i = 0;
	while (i < ft_count_line(keys))
	{
		if (!ft_check_key(keys[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_error(char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_cd_error(char *cmd, int i, char **old, char **pwd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (i == 0)
		ft_putstr_fd("not set", 2);
	else if (i == 1)
		ft_putstr_fd("No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	if (old)
	{
		if (*old)
			free(*old);
	}
	if (pwd)
	{
		if (*pwd)
			free(*pwd);
	}
	return (1);
}

void	ft_addkey(t_list *list, char **keys, char **args)
{
	int		is_exist;
	int		i;
	t_list	*tmp;

	tmp = list;
	i = 0;
	while (i < ft_count_line(keys))
	{
		is_exist = 0;
		while (list)
		{
			if (!ft_strncmp(list->content, keys[i], ft_strlen(keys[i])))
				is_exist = 1;
			list = list->next;
		}
		list = tmp;
		if (!is_exist && ft_check_key(keys[i]) == 1)
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(args[i])));
		if (ft_check_key(keys[i]) == 0)
			ft_export_error(keys[i], 0, 0);
		else if (ft_check_key(keys[i]) == -1)
			ft_export_error(NULL, 1, keys[i][1]);
		i++;
	}
}
