/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/23 14:14:41 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "struct.h"
# include "buitlin.h"

int	ft_lstfree(t_d_list **list);
int	ft_is_builtin(t_data *data);
int	ft_count_line(char **strings);

void	ft_init(char **env, t_data *data);
void	ft_add_front_list(t_d_list **list, t_d_list *new);
void	ft_add_back_list(t_d_list **list, t_d_list *new);
void	get_input(t_data *data);
void	waiting_signal(void);
void	ft_free_split(char **strings);
char	**ft_dup(char **s2);
void    ft_redir(t_list *out, int type);
void    ft_execute(t_data *data);

t_d_list	*ft_newlist(char *content);
#endif