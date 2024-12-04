/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:20:39 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/04 10:52:39 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_error(char *str)
{
	if (str[0] == '<' || str[0] == '>')
	{
		ft_putstr_fd("MINISHELL: syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		write(2, "'\n", 2);
		return (0);
	}
	return (1);
}

int	ft_notsep(char c)
{
	int		i;
	char	*sep;

	i = 0;
	sep = ft_strdup(" ;\'\"$<>|");
	while (sep[i])
	{
		if (sep[i] == c)
		{
			free (sep);
			return (0);
		}
		i++;
	}
	free (sep);
	return (1);
}

int	ft_iswite_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_end_pip(char *str)
{
	if (str[ft_strlen(str) - 1] == '|')
		return (1);
	return (0);
}

int	check_after_child(t_data *data)
{
	waitpid(data->signal->pid, &(data->signal->stats), 0);
	if (WIFEXITED(data->signal->stats))
	{
		if (WEXITSTATUS(data->signal->stats))
		{
			data->return_value = WEXITSTATUS(data->signal->stats);
			data->error = 1;
		}
	}
	if (WIFSIGNALED(data->signal->stats))
	{
		data->return_value = WTERMSIG(data->signal->stats) + 128;
		data->error = 1;
	}
	return (0);
}
