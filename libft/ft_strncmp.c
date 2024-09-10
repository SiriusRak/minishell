/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:57:06 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/10 13:25:30 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (*(char *)(s1 + i) == *(char *)(s2 + i) && i < n)
		i++;
	if (i < n)
		return (*(char *)(s1 + i) - *(char *)(s2 + i));
	return (0);
}
