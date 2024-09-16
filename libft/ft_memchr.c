/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:19:56 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/10 13:23:30 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*out;

	i = 0;
	p = (unsigned char *)s;
	while (n > i)
	{
		if (p[i] == (unsigned char)c)
		{
			out = (unsigned char *)&p[i];
			return (out);
		}
		i++;
	}
	return (0);
}
