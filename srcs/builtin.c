/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:35:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/29 10:47:48 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtin_echo(char **arg)
{
	int	newline;
	int	i;

	i = 0;
	newline = 1;
	while (ft_strncmp(arg[i], "-n", 2) == 0 && i < ft_count_line(arg))
	{
		if (arg[i][2] == '\0' || arg[i][2] == 'n')
		{
			newline = 0;
			i++;
		}
		else
			break;
	}
	while (i < ft_count_line(arg))
	{
		printf("%s",arg[i]);
		if (i + 1 < ft_count_line(arg))
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
int	ft_buitlin_cd(char **arg, t_data *data)
{
	char	*value;
	char	*old_pwd;
	char	*pwd;

	if (ft_count_line(arg) > 1)
	{
		ft_print_error("cd", "too many arguments\n");
		return (1);
	}
	else
	{
		value = ft_get_value("HOME", data->env);
		if (value)
		{
			pwd = ft_get_value("PWD", data->env);
			if (!arg[0] && value)
				chdir(value);
			else if (!ft_strncmp(arg[0], "-", ft_strlen(arg[0])))
			{
				old_pwd = ft_get_value("OLDPWD", data->env);
				printf("%s\n", old_pwd);
				chdir(old_pwd);
				ft_change_pwd(data, &old_pwd, &pwd, 0);
			}
			else
			{
				old_pwd = ft_strdup(pwd);
				if (chdir(arg[0]) == 0)
					ft_change_pwd(data, &old_pwd, &pwd, 1);
				else
				{
					ft_putstr_fd("cd: ", 2);
					ft_print_error(arg[0], "No such file or directory\n");
					return (1);
				}
			}
			if (value)
				free(value);
		}
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	return (0);
}
int	ft_builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("pwd");
		return (1);
	}
	return (0);
}

int	ft_builtin_exit(t_data *data, char **arg)
{
	int	len;

	len = ft_count_line(arg);
	printf("exit\n");
	if (len > 1)
	{
		ft_print_error("exit", "too many arguments\n");
		return (1);
	}
	if (len == 1 && !ft_check_num(arg[0]))
	{
		ft_print_error(arg[0], "numeric argument required\n");
		ft_exit_1(data, 255);
	}
	else if (len == 1 && ft_check_num(arg[0]))
		ft_exit_1(data, ft_atoi(arg[0]));
	ft_exit_1(data, data->return_value);
	return (0);
}
int	ft_builtin_env(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}
