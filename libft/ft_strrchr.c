/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:34:43 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/10 13:25:43 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	len;

	str = (char *)s;
	if (!c)
		return (str + ft_strlen(str));
	len = ft_strlen(str) - 1;
	while ((int)len >= 0)
	{
		if (str[len] == (char)c)
			return (str + len);
		len --;
	}
	return (NULL);
}
