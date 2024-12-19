/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:43:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/19 15:44:22 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_change_pwd(t_data *data, char **old_pwd, char **pwd, int i)
{
	char	**values;
	char	cwd[1024];

	data->keys = malloc(sizeof(char *) * 3);
	values = malloc(sizeof(char *) * 3);
	data->keys[0] = ft_strdup("PWD");
	data->keys[1] = ft_strdup("OLDPWD");
	data->keys[2] = 0;
	if (i == 0)
	{
		values[0] = ft_strjoin_3("PWD=", *old_pwd);
		values[1] = ft_strjoin_3("OLDPWD=", *pwd);
	}
	else
	{
		values[0] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
		values[1] = ft_strjoin_3("OLDPWD=", *old_pwd);
		free(*pwd);
	}
	values[2] = 0;
	ft_builtin_export(data, values);
	ft_free_split(values);
}

void	ft_restore_fd(t_data *data, int saved_fd)
{
	if (dup2(saved_fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(saved_fd);
	data->saved_fd = -1;
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
			break ;
	}
	return (i);
}

int	ft_manage_unset(char *key, t_list *curr, t_list *prev, t_data *data)
{
	if (!ft_strncmp(curr->content, key, ft_strlen(key)))
	{
		if (prev)
			prev->next = curr->next;
		else
			data->env = curr->next;
		free(curr->content);
		free(curr);
		return (1);
	}
	return (0);
}

int	ft_check_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && (arg[i] == '+' || arg[i] == '-'))
			;
		else if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}
