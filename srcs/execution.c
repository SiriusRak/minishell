/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:21:42 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/23 17:14:12 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_execute(t_data *data)
{
    if (data->list->token->out != NULL)
        ft_redir(data->list->token->out, data->list->token->out->type);
}