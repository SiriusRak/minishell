/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:44:35 by enarindr          #+#    #+#             */
/*   Updated: 2024/04/06 06:52:27 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_first_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

char	*ft_next_line(char *buff, int start)
{
	char	*rest;
	int		i;

	i = 0;
	while (buff[start++])
		i++;
	rest = (char *)ft_calloc_get (sizeof(char), (i + 1));
	if (!rest)
		return (NULL);
	start -= i;
	start--;
	i = 0;
	while (buff[start])
		rest[i++] = buff[start++];
	free (buff);
	return (rest);
}

char	*ft_get_word(char *rest, int fd)
{
	int		sz;
	char	*new;

	sz = 1;
	while (!(ft_first_len(rest)))
	{
		new = (char *)ft_calloc_get (sizeof(char), (BUFFER_SIZE + 1));
		if (!new)
			return (NULL);
		sz = read(fd, new, BUFFER_SIZE);
		if (sz < 0)
		{
			free(new);
			free (rest);
			rest = NULL;
			return (rest);
		}
		if (sz == 0)
		{
			free(new);
			return (rest);
		}
		rest = ft_strjoin_get(rest, new);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_get_word(buff, fd);
	if (!buff || *buff == '\0')
	{
		free (buff);
		buff = NULL;
		return (NULL);
	}
	result = ft_strdup_get(buff, ft_first_len(buff) - 1);
	buff = ft_next_line(buff, ft_strlen_get(result));
	return (result);
}
