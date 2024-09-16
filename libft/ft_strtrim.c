/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:19:52 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/10 13:25:49 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (ft_strchr(set, s1[i]) && i < len)
		i++;
	if (i >= len)
		return (ft_strdup(s1 + len));
	while (ft_strchr(set, s1[len - 1]) && (int)(len - 1) >= 0)
		len--;
	str = malloc(sizeof(char) * (len - i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, len - i + 1);
	return (str);
}
