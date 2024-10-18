/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:53 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/28 16:06:31 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sep(char c, char *sep)
{
	int		i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_word(char const *s, char *sep)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] && ft_is_sep(s[i], sep))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && !ft_is_sep(s[i], sep))
			i++;
	}
	return (count);
}

static int	ft_strlen_sep(char const *s, char *sep)
{
	int	i;

	i = 0;
	while (s[i] && !ft_is_sep(s[i], sep))
		i++;
	return (i);
}

static char	*ft_word(char const *s, char *sep)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(s, sep);
	word = ft_calloc(sizeof(char), (len_word + 3));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char *sep)
{
	char	**strings;
	int		i;

	i = 0;
	strings = malloc(sizeof(char *) * (ft_count_word(s, sep) + 1));
	if (!strings)
		return (NULL);
	while (*s)
	{
		while (*s && ft_is_sep(*s, sep))
			s++;
		if (*s != '\0')
		{
			strings[i] = ft_word(s, sep);
			i++;
		}
		while (*s && !ft_is_sep(*s, sep))
			s++;
	}
	strings[i] = NULL;
	return (strings);
}
