/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:43:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/23 15:40:44 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_pwd(t_data *data, char **old_pwd, char **pwd, int i)
{
	char	**keys;
	char	**values;
	char	cwd[1024];

	keys = malloc(sizeof(char *) * 3);
	values = malloc(sizeof(char *) * 3);
	keys[0] = ft_strdup("PWD");
	keys[1] = ft_strdup("OLDPWD");
	keys[2] = 0;
	if (i == 0)
	{
		values[0] = ft_strjoin("PWD=", *old_pwd);
		values[1] = ft_strjoin("OLDPWD=", *pwd);
	}
	else
	{
		values[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
		values[1] = ft_strjoin("OLDPWD=", *old_pwd);
	}
	*old_pwd = ft_substr(values[1], 7, ft_strlen(values[1]) - 7);
	*pwd = ft_substr(values[0], 4, ft_strlen(values[0]) - 4);
	values[2] = 0;
	ft_builtin_export(keys, data, values);
	ft_free_split(keys);
	ft_free_split(values);
}

void	ft_restore_fd(int saved_fd)
{
	if (dup2(saved_fd, STDOUT_FILENO) == -1)
		perror("dup2");
		//exit_free
	close(saved_fd);
}

int	ft_check_arg(char *arg, int *newline)
{
	int	i;

	while (arg && arg[0] == '-' && arg[1] == 'n')
	{
		i = 1;
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
		{
			*newline = 0;
			i++;
		}
		else
			break;
	}
	return (i);
}
