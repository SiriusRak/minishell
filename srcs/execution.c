/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:21:42 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/07 13:56:51 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_cmd(t_data *data)
{
	 
}

void	ft_check_cmd(t_data *data)
{
	t_d_list	*head;

	if (data->list->token->out != NULL)
		ft_redir(data->list->token->out, data->list->token->out->type);
	head = data->list;
	while (data->list)
	{
		data->list->token->path = ft_find_in_path(data->list->token->cmd);
		if (!ft_is_builtin(data->list->token))
			perror("cmd");
		else if (!data->list->token->path)
			perror("cmd");
		data->list = data->list->next;
	}
	data->list = head;
}

void	ft_execute(t_data *data)
{
	char	*arg;

	arg = data->list->token->arg;
	ft_check_cmd(data);
	if (ft_is_builtin(data->list->token->cmd))
		ft_execute_builtin(data, data->list->token->cmd, arg);
	else if (!ft_is_builtin(data->list->token->cmd))
		ft_execute_cmd(data);
}
