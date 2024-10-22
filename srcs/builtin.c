/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:35:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/22 16:51:14 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//taf: gerer -n
void	ft_builtin_echo(char **arg)
{
	int	newline;
	int	i;

	i = 0;
	newline = 1;
	while (i < ft_count_line(arg))
	{
		while (ft_strncmp(arg[i], "-n", 3) == 0 && i < ft_count_line(arg))
		{
			newline = 0;
			i++;
		}
		if (i < ft_count_line(arg))
			printf("%s", arg[i]);
		if (i < ft_count_line(arg) - 1)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
void	ft_buitlin_cd(char **arg, t_data *data)
{
	if (ft_count_line(arg) > 1)
		perror("too many arg");
	else
	{
		if (!arg[0] || !ft_strncmp(arg[0], "~", ft_strlen(arg[0])))
		{
			chdir((getenv("HOME")));
			ft_change_pwd(data, &data->pwd, &data->pwd, 1);
		}
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
void	ft_builtin_exit(char **arg)
{
	int	len;

	len = ft_count_line(arg);
	printf("exit\n");
	if (len > 1)
	{
		perror("Too many arg");
		//continue
	}
	if (arg[0])
	{
		//code
	}
	//exit_function
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
