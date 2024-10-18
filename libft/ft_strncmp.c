/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:57:06 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/24 09:53:50 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 && s2)
	{
		while (*(char *)(s1 + i) == *(char *)(s2 + i) && i < n)
			i++;
		if (i < n)
			return (*(char *)(s1 + i) - *(char *)(s2 + i));
	}
	return (0);
}
