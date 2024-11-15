/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:35:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/15 19:28:10 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_builtin_echo(char **arg)
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
		printf("%s", arg[i]);
		if (i + 1 < ft_count_line(arg))
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
void	ft_buitlin_cd(char **arg, t_data *data)
{
	char	*value;

	if (ft_count_line(arg) > 1)
		perror("too many arg");
	else
	{
		value = ft_get_value("HOME", data->env);
		if (value)
		{
			if (!arg[0] && value)
				chdir(value);
			else if (!ft_strncmp(arg[0], "-", ft_strlen(arg[0])))
			{
				printf("%s\n", data->old_pwd);
				chdir(data->old_pwd);
				ft_change_pwd(data, &data->old_pwd, &data->pwd, 0);
			}
			else
			{
				data->old_pwd = ft_strdup(data->pwd);
				if (chdir(arg[0]) == 0)
					ft_change_pwd(data, &data->old_pwd, &data->pwd, 1);
				else
					perror(arg[0]);
			}
			if (value)
				free(value);
		}
		else
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
}
void	ft_builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}
void	ft_builtin_exit(t_data *data, char **arg)
{
	int	len;

	len = ft_count_line(arg);
	printf("exit\n");
	if (len > 1)
	{
		perror("Too many arg");
		//continue
	}
	if (len == 1 && !ft_check_num(arg[0]))
		ft_putstr_fd("minishell: numeric argument required\n", 2);
	ft_exit_1(data);
}
void	ft_builtin_env(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
