/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:36 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/16 16:33:01 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (1);
	else if (!ft_strncmp(cmd, "exit", len))
		return (1);
	else if (!ft_strncmp(cmd, "env", len))
		return (1);
	else if (!ft_strncmp(cmd, "export", len))
		return (1);
	else if (!ft_strncmp(cmd, "unset", len))
		return (1);
	else if (!ft_strncmp(cmd, "cd", len))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", len))
		return (1);
	return (0);
}

char	*ft_find_in_path(char *cmd)
{
	char	*path;
	char	full_path[1024];
	char	**splitted_path;
	int		i;

	i = 0;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	splitted_path = ft_split(path, ":");
	while (splitted_path[i])
	{
		ft_strlcpy(full_path, splitted_path[i], ft_strlen(splitted_path[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd, ft_strlen(full_path) + ft_strlen(cmd) + 1);
		if (!access(full_path, X_OK))
		{
			ft_free_split(splitted_path);
			return (ft_strdup(full_path));
		}
		i++;
	}
	ft_free_split(splitted_path);
	return (NULL);
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
