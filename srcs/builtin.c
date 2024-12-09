/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:35:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/09 10:37:14 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtin_echo(char **arg, t_data *data)
{
	int	newline;
	int	i;

	i = 0;
	newline = 1;
	while (ft_is_n(arg[i]) && i < ft_count_line(arg))
	{
		newline = 0;
		i++;
	}
	ft_print_echo(i, arg, data, newline);
	return (0);
}

int	ft_buitlin_cd(char **arg, t_data *data)
{
	char	*value;
	char	*pwd;

	if (ft_count_line(arg) > 1)
	{
		ft_print_error("cd", "too many arguments");
		return (1);
	}
	else
	{
		value = ft_get_value("HOME", data->env);
		if (value)
		{
			pwd = ft_get_value("PWD", data->env);
			if (ft_manage_cd(data, &value, arg[0], &pwd))
				return (1);
		}
		else
			return (ft_cd_error("HOME", 0, NULL, NULL));
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
	if (!ft_check_num(arg[0]))
	{
		ft_print_error(arg[0], "numeric argument required");
		ft_exit_1(data, 2);
	}
	if (len > 1)
	{
		ft_print_error("exit", "too many arguments");
		return (1);
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
