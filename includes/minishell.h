/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/23 14:21:35 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"

typedef	struct	s_type	t_type;
typedef struct s_token	t_token;
typedef struct s_d_list	t_d_list;
typedef struct  s_data	t_data;

typedef	struct s_token
{
	t_list	*arg;
	t_list	*cmd;
	t_list	*heredoc;
	t_list	*in;
	t_list	*out;
	t_list	*out_two;
	t_list	*var;
	t_list	*var_two;
	char	*name;
	int		pip;
}				t_token;

typedef struct s_d_list
{
	struct s_d_list	*prev;
	t_token			*token;
	struct s_d_list	*next;
}				t_d_list;

typedef struct  s_data
{
	char		**env;
	char		**tab;
	char		*input;
	char		*sep;
	t_d_list	*list;
}				t_data;

int	ft_lstfree(t_d_list **list);
int	ft_init(char **env, t_data *data);
int	ft_is_builtin(char *cmd);

void	ft_add_front_list(t_d_list **list, t_d_list *new);
void	ft_add_back_list(t_d_list **list, t_d_list *new);
void	get_input(t_data *data);
void	waiting_signal(void);

t_d_list	*ft_newlist(char *content);

#endif
