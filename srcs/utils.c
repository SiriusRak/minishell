/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:36 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/04 13:57:49 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len) && len == 4)
		return (1);
	else if (!ft_strncmp(cmd, "exit", len) && len == 4)
		return (1);
	else if (!ft_strncmp(cmd, "env", len) && len == 3)
		return (1);
	else if (!ft_strncmp(cmd, "export", len) && len == 6)
		return (1);
	else if (!ft_strncmp(cmd, "unset", len) && len == 5)
		return (1);
	else if (!ft_strncmp(cmd, "cd", len) && len == 2)
		return (1);
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
		return (1);
	return (0);
}

char	*ft_find_in_path(t_data *data, char *cmd)
{
	char	*path;
	char	full_path[1024];
	char	**s_path;

	path = ft_get_value("PATH", data->env);
	if (!path)
	{
		data->path = 0;
		return (NULL);
	}
	s_path = ft_split(path, ":");
	free(path);
	return (ft_manage_path(s_path, full_path, cmd));
}

int	ft_count_line(char **strings)
{
	int	height;

	height = 0;
	while (strings[height] != NULL)
		height++;
	return (height);
}

t_list	*ft_duplicate(char **str)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = 0;
	while (str[i])
	{
		list = ft_add_node(list, str[i]);
		i++;
	}
	return (list);
}

char	**ft_sort_tab(char **tab)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < ft_count_line(tab) - 1)
	{
		j = 0;
		while (j < ft_count_line(tab) - 1 - i)
		{
			if (ft_strncmp(tab[j], tab[j + 1], ft_strlen(tab[j])) > 0)
			{
				tmp = ft_strdup(tab[j]);
				tab[j] = ft_strdup(tab[j + 1]);
				tab[j + 1] = ft_strdup(tmp);
			}
			j++;
		}
		i++;
	}
	free(tmp);
	return (tab);
}
