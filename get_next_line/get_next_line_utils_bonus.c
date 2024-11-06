/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:58:17 by enarindr          #+#    #+#             */
/*   Updated: 2024/04/05 18:15:01 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	unsigned int	i;

	if (!s || *s == '\0')
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (size != 0 && nmemb * size > (size_t) - 1)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	k;
	char			*new;

	k = -1;
	if (!s1)
		s1 = ft_calloc(1, 1);
	i = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)ft_calloc (sizeof(char), i + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	while (s2[++k])
		new[i + k] = s2[k];
	free (s1);
	free (s2);
	return (new);
}

char	*ft_strdup(char *s, int len)
{
	int		i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	if (len == -1)
	{
		while (s[i])
			i++;
		len = i;
	}
	while (s[i] && i <= len)
		i++;
	new = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!new)
		return (NULL);
	while (i--)
		new[i] = s[i];
	return (new);
}
