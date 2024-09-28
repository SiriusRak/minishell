/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 08:39:55 by enarindr          #+#    #+#             */
/*   Updated: 2024/09/28 08:59:27 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_print_list(t_list **list)
{
    t_list  *temp;
    int     i;

    i = 0;
    temp = *list;
    while (temp)
    {
        printf("[heredoc %d:]\n%s\n", i, temp->content);
        i++;
        temp = temp->next;
    }
}