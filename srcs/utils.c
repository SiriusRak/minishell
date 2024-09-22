/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:54:36 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/22 15:56:28 by enarindr         ###   ########.fr       */
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
			return (ft_str)
		}
		i++;
	}
	printf("%s\n", path);
	return (NULL);
}

int	ft_is_cmd(char *cmd)
{

}
