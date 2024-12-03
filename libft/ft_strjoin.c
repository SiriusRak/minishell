/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:11:32 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/03 16:32:54 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, len + 1);
	res[len] = '\0';
	return (res);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (ft_strlen(s2) == 0)
		return (s1);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, len + 1);
	res[len] = '\0';
	free(s1);
	free(s2);
	return (res);
}

char	*ft_strjoin_3(char *s1, char *s2)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!s1)
		return (s2);
	if (ft_strlen(s2) == 0)
		return (s1);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, len + 1);
	res[len] = '\0';
	free(s2);
	return (res);
}
