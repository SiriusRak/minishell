/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epure.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:12:01 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/11 14:24:28 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_epure_line(char *str)
{
    int     len;
    int     i;
    int     j;
    char    *new;

    len = ft_strlen(str);
    i = 0;
    j = 0;
    new = ft_calloc(sizeof(char), len + 1);
    if (!new)
        return (NULL);
    while (str[i] && ft_iswite_space(str[i]))
        i++;
    while (str[i])
        new[j++] = str[i++];
    new[j] = '\0';
    len = ft_strlen(new) - 1;
    while (ft_iswite_space(new[len]) && len > 0)
    {
        new[len] = '\0';
        len--;
    }
    free(str);
	return (new);
}
