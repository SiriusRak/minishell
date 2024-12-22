/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:51:46 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/10 12:58:50 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_manage_path(char **s_path, char *f_path, char *cmd)
{
	int	i;

	i = 0;
	while (s_path[i])
	{
		ft_strlcpy(f_path, s_path[i], ft_strlen(s_path[i]) + 1);
		ft_strlcat(f_path, "/", ft_strlen(f_path) + 2);
		ft_strlcat(f_path, cmd, ft_strlen(f_path) + ft_strlen(cmd) + 1);
		if (!access(f_path, F_OK))
		{
			ft_free_split(s_path);
			return (ft_strdup(f_path));
		}
		i++;
	}
	ft_free_split(s_path);
	return (NULL);
}

int	ft_take_pipe_ext(t_data *data, int i, char *str, int *start)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = ft_find_next_quote(str, i, str[i], data);
			if (!i)
				return (-1);
		}
		if (str[i] && str[i] == '|')
		{
			if (ft_pipe_error(str, i))
			{
				ft_exit_pipe(str, data);
				return (-1);
			}
			i = ft_add_list(data, *start, i, str);
			*start = i + 1;
		}
		i++;
	}
	return (i);
}

int	ft_manage_cmd(t_data *data, int i)
{
	char	*cmd;

	if (!data->list->token->cmd)
	{
		if (data->saved_fd >= 0)
			ft_restore_fd(data, data->saved_fd);
		if (data->list->token->in)
		{
			close (STDIN_FILENO);
			open ("/dev/tty", O_RDONLY);
		}
		return (1);
	}
	else
	{
		cmd = data->list->token->cmd->content;
		data->checker = ft_manage_exec(data, cmd, i);
	}
	return (0);
}
