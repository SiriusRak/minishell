/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:36 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/20 17:07:21 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_builtin(t_data *data)
{
	size_t	len;
	char	*cmd;

	cmd = data->list->token->cmd;
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

char	**ft_dup(char **s2)
{
	int		len;
	int		i;
	char	**str;

	i = 0;
	len = ft_count_line(s2);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	while (s2[i])
	{
		str[i] = ft_strdup(s2[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}
