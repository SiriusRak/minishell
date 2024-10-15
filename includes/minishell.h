/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/15 16:56:00 by enarindr         ###   ########.fr       */
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
	t_list	*cmd;
	t_list	*in;
	t_list	*out;
	char	*name;
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
	char		*input;
	char		*prompt;
	char		*history;
	t_d_list	*list;
}				t_data;

/*debug start*/
int		ft_print_all(t_data *data);
/*debug end*/

int		ft_lstfree(t_d_list **list);
int		ft_free_t_d_list(t_data *data);
int     ft_free_tab(char **tab);
int		ft_iswite_space(char c);
int		ft_notsep(char	c);
int		ft_get_input(t_data *data);
int		ft_add_list(t_data *data, int start, int i, char *str);
int		ft_find_next_quote(char *str, int start, int type, t_data *data);
int		ft_find_next_quote_2(char *str, int start, int type);
int		ft_exit_quote(char *str, t_data *data);
int		ft_get_input(t_data *data);
int		ft_take_pipe(char *str, t_data *data);
int		ft_clear_history(t_data *data);
int		ft_exit(char *str);
int		ft_free_data(t_data *data);
int		ft_pipe_error(char *str, int i);
int		ft_check_list(t_data *data);
int		ft_lex(t_d_list *list, char *str);
int		ft_lex_ext(t_d_list *list, char **tab, int i);
int		ft_pars(t_d_list *list);
int		ft_pars_ext(char *str, char **tmp, int i, char c);
int		ft_add_out(t_d_list *list, char *str, int i);
int		ft_add_in(t_d_list *list, char *str, int i);
int		ft_add_cmd(t_d_list *list, char *str);
int		ft_check_error(char *str);

char	*ft_epure_line(char *str);
char	*ft_epure_redir(char *str);
char	*ft_arrange_prev_redir(char *str);
char	*ft_arrange_back_redir(char *str);
char	*ft_epure_space(char *str);

void    ft_exit_1(t_data *data);
void    ft_exit_2(t_data *data);
void	ft_exit_pipe(char *str, t_data *data);
void    ft_init(t_data *data);
void	ft_add_front_list(t_d_list **list, t_d_list *new);
void	ft_add_back_list(t_d_list **list, t_d_list *new);
void	signal_handler(int	sig);
void	waiting_signal(void);
void	ft_clear_input(t_data *data);

t_d_list	*ft_newlist(char *content);


#endif
