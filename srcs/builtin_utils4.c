/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:20:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/19 15:58:53 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_n(char *str)
{
	int		i;

	i = 0;
	if (str && str[i] && str[i] == '-' && str[i + 1] && str[i + 1] == 'n')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_print_echo(int i, char **arg, t_data *data, int newline)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		while (i < ft_count_line(arg))
		{
			printf("%s", arg[i]);
			if (i + 1 < ft_count_line(arg))
				printf(" ");
			i++;
		}
		if (newline)
			printf("\n");
		ft_free_split(arg);
		free(data->checker);
		ft_exit_child(data, 0);
	}
	else
		wait (0);
	return (1);
}

int	ft_isback(t_data *data, char *pwd, char *oldpwd, char **value)
{
	oldpwd = ft_get_value("OLDPWD", data->env);
	if (!oldpwd)
	{
		free(*value);
		return (ft_cd_error("OLDPWD", 0, NULL, &pwd));
	}
	printf("%s\n", oldpwd);
	chdir(oldpwd);
	ft_change_pwd(data, &oldpwd, &pwd, 0);
	free(*value);
	return (0);
}

int	ft_check_cd(char **value, char **pwd, char*arg)
{
	if (!arg && *value)
	{
		free(*pwd);
		chdir(*value);
		return (1);
	}
	return (0);
}

int	ft_manage_cd(t_data *data, char **value, char *arg, char **pwd)
{
	char	*oldpwd;

	oldpwd = data->old_pwd;
	if (!*pwd)
	{
		free(*value);
		return (ft_cd_error("PWD", 0, NULL, NULL));
	}
	if (ft_check_cd(value, pwd, arg))
		;
	else if (!ft_strncmp(arg, "-", ft_strlen(arg)))
		return (ft_isback(data, *pwd, oldpwd, value));
	else
	{
		oldpwd = ft_strdup(*pwd);
		if (chdir(arg) == 0)
			ft_change_pwd(data, &oldpwd, pwd, 1);
		else
		{
			free(*value);
			return (ft_cd_error(arg, 1, &oldpwd, pwd));
		}
	}
	free(*value);
	return (0);
}
