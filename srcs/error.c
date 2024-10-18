/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:57:26 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/11 17:00:32 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipe_error(char *str, int i)
{
	i++;
	while (str[i] && ft_iswite_space(str[i]))
		i++;
	if (str[i] == '|')
		return (1);
	return (0);	
}
