/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:20:38 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/10 13:23:55 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*s1;
	char	*s2;

	s1 = dest;
	s2 = (char *)src;
	while (n-- > 0)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	return (dest);
}
