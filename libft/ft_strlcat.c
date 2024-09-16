/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 08:20:12 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/10 13:25:08 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	i = 0;
	if (len < size)
	{
		while (src[i] != '\0' && i + len < size - 1)
		{
			dst[len + i] = src[i];
			i++;
		}
		dst[len + i] = '\0';
		while (src[i] != '\0')
			i++;
	}
	else
	{
		while (src[i] != '\0')
			i++;
		return (i + size);
	}
	return (len + i);
}
