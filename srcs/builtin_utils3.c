/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:48:21 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/29 14:58:00 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_key(char *key)
{
	int	i;

	i = 0;
	if (key[0] == '-' && ft_strlen(key) > 2)
		return (-1);
	if (key[0] != '_' &&  !isalpha(key[i]))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_allkey(char **keys)
{
	int	i;

	i = 0;
	while (i < ft_count_line(keys))
	{
		if (!ft_check_key(keys[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_error(char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}
