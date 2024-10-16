/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:35:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/14 17:07:07 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_builtin_echo(char **arg)
{
	int	newline;
	int	i;
	int	j;

	i = 0;
	newline = 1;
	while (i < ft_count_line(arg))
	{
		j = 0;
		if (ft_strncmp(arg[0], "-n ", 3) == 0)
		{
			newline = 0;
			j += 3;
		}
		while (arg[i][j] == ' ')
			j++;
		while (arg[i][j])
		{
			printf("%c", arg[i][j]);
			j++;
		}
		if (newline)
			printf("\n");
		i++;
	}
}
void	ft_buitlin_cd(char **arg)
{
	if (ft_count_line(arg) > 1)
		perror("too many arg");
	else
	{
		if (!arg[0])
		chdir((getenv("HOME")));
		else if (chdir(arg[0]) != 0)
		{
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
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
