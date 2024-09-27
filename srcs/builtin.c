/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:35:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/27 13:54:43 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_builtin_echo(char *arg)
{
	int	newline;
	int	i;

	i = 0;
	newline = 1;
	if (ft_strncmp(arg, "-n ", 3) == 0)
	{
		newline = 0;
		i += 3;
	}
	while (arg[i] == ' ')
		i++;
	while (arg[i])
	{
		printf("%c", arg[i]);
		i++;
	}
	if (newline)
		printf("\n");
}
void	ft_buitlin_cd(char *arg)
{
	if (!arg)
		chdir((getenv("HOME")));
	else if (chdir(arg) != 0)
	{
		perror(arg);
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
void	ft_builtin_exit(char *arg)
{
	int	exit_code;

	exit_code = 0;
	if (arg)
		exit_code = ft_atoi(arg);
	exit(exit_code);
}
void	ft_builtin_env(t_data *data)
{
	t_list	*tmp;

	tmp = data->env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
