/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:46:17 by enarindr          #+#    #+#             */
/*   Updated: 2024/09/25 17:38:14 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_exit(t_data *data)
{
	int i;

	i = 0;
	while ((data->env)[i])
	{
		free ((data->env)[i]);
		i++;
	}
	free (data->env);
	free (data->sep);
	free (data->input);
	if (data->list->token->heredoc)
		ft_lstclear_2(&(data->list->token->heredoc));
	// free (data->list->token->heredoc);
	free (data->list->token);
	free (data->list);
	exit (0);
	return (0);
}