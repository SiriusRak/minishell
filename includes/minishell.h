/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/18 11:45:28 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "struct.h"
# include "builtin.h"

int	ft_lstfree(t_d_list **list);
int	ft_count_line(char **strings);

void    ft_exit_1(t_data *data);
void    ft_exit_2(t_data *data);
void	ft_exit_pipe(char *str, t_data *data);
void    ft_init(t_data *data, char **env);
void	ft_add_front_list(t_d_list **list, t_d_list *new);
void	ft_add_back_list(t_d_list **list, t_d_list *new);
void	signal_handler(int	sig);
void	waiting_signal(void);


void	ft_free_split(char **strings);
void    ft_redir(t_list *out);
void    ft_execute(t_data *data);
char	**ft_sort_tab(char **tab);
void	ft_export_no_arg(t_data *data);
void	ft_execute_builtin(t_data *data, char *cmd);

char	**ft_lst_to_char(t_list *list, int type);

t_list      *ft_duplicate(char **str);
void	ft_clear_input(t_data *data);

t_d_list	*ft_newlist(char *content, t_data *data);


#endif
