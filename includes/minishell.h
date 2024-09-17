/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/17 07:28:47 by enarindr         ###   ########.fr       */
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

typedef struct s_token	t_token;
typedef struct s_d_list	t_d_list;

typedef	struct s_token
{
	int		cmd;
	int 	arg;
	int 	redir;
	int 	pip;
	char	*name;
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
	char		*input;
	t_d_list	*list;
	char		**tab;
	
}       t_data;

int	ft_lstfree(t_d_list **list);
int	ft_init(char **env, t_data *data);

void	ft_add_front_list(t_d_list **list, t_d_list *new);
void	ft_add_back_list(t_d_list **list, t_d_list *new);
void	get_input(t_data *data);
void	waiting_signal(void);

t_d_list	*ft_newlist(char *content);
#endif