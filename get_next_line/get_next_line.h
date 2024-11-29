/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:12:09 by enarindr          #+#    #+#             */
/*   Updated: 2024/04/06 07:04:12 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

size_t	ft_strlen_get(char *s);

int		ft_first_len(char *str);

char	*ft_strdup_get(char *s, int len);
char	*ft_get_word(char *rest, int fd);
char	*get_next_line(int fd);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_next_line(char *buff, int start);

void	ft_bzero_get(void *s, size_t n);
void	*ft_calloc_get(size_t nmemb, size_t size);

#endif
