/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/09 08:06:05 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"

// typedef	struct	s_type	t_type;
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
	t_list	*var;
	t_list	*var_two;
	char	*name;
	int		pip;
}				t_token;

typedef struct s_d_list
{
	struct s_d_list	*prev;
	t_token			*token;
	t_data			*data;
	struct s_d_list	*next;
}				t_d_list;

typedef struct  s_data
{
	char		**env;
	char		**tab;
	char		*input;
	char		*prompt;
	int			pipe;
	t_d_list	*list;
	t_d_list	*final_list;
}				t_data;

/*debug start*/
void    ft_print_list(t_list **list);
int		ft_print_all(t_data *data);

/*debug end*/

int		ft_lstfree(t_d_list **list);
int		ft_init(char **env, t_data *data);
int		ft_is_builtin(char *cmd);
int		ft_notsep(char	c);

int		ft_iswite_space(char c);
int 	ft_exit(t_data *data, int i);
int		get_input(t_data *data);
int		ft_is_heredoc(char	*str);
int		ft_init(char **env, t_data *data);
int		ft_end_pip(char *str);
int		ft_free_loop(t_data *data, int i);
int		ft_d_free_list(t_d_list **list);
int		ft_t_free_list(t_list **list);

char	*ft_epure_line(char *str);

void	ft_add_front_list(t_d_list **list, t_d_list *new);
void	ft_add_back_list(t_d_list **list, t_d_list *new);
void	waiting_signal(void);
void	ft_init_list(t_d_list **list);
void	ft_heredoc(t_d_list *list);

t_d_list	*ft_newlist(char *content);


#endif
