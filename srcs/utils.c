/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:36 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/27 15:27:58 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(t_data *data)
{
	size_t	len;
	char	*cmd;
	char	*arg;

	cmd = (char *)data->list->token->cmd;
	arg = (char *)data->list->token->arg;
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		ft_builtin_echo(arg);
	else if (!ft_strncmp(cmd, "exit", len))
		ft_builtin_exit(arg);
	else if (!ft_strncmp(cmd, "env", len))
		ft_builtin_env(data);
	// else if (!ft_strncmp(cmd, "export", len))
		// ft_builtin_export(cmd, data, arg);
	else if (!ft_strncmp(cmd, "unset", len))
		return (1);
	else if (!ft_strncmp(cmd, "cd", len))
		ft_buitlin_cd(arg);
	else if (!ft_strncmp(cmd, "pwd", len))
		ft_builtin_pwd();
	return (0);
}

char	*find_in_path(char *cmd)
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
		ft_strlcpy(full_path, splitted_path[i], ft_strlen(splitted_path[i]));
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 1);
		ft_strlcat(full_path, cmd, ft_strlen(full_path) + ft_strlen(cmd));
		if (!access(full_path, X_OK))
		{
			// return (ft_str)
		}
		i++;
	}
	printf("%s\n", path);
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

void	ft_swap(char *a, char *b)
{
	char *tmp;
	
	tmp = ft_strdup(a);
	a = ft_strdup(b);
	b = ft_strdup(tmp);
	free(tmp);
}

void	ft_sort_tab(char **tab)
{
	int		i;
	int		j;
	char	*key;
	size_t	k_len;

	i = 1;
	while (i < ft_count_line(tab))
	{
		key = tab[i];
		k_len = ft_strlen(key);
		j = i - 1;
		while (j >= 0)
		{
			if (strncmp(tab[j], key, k_len) > 0)
			{
				tab[j + 1] = tab[j];
				j = j - 1;
			}
			else
				break;
		}
		tab[j + 1] = key;
		i++;
	}
}
