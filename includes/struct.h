/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:44:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/19 14:23:14 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token	t_token;
typedef struct s_d_list	t_d_list;

typedef	struct	s_cmd
{
	char	*heredoc;
	char	*cmd;
	char	*arg;
	char	*out_file;
	char	*in_file;
}				t_cmd;

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
    char        **path;
	t_d_list	*list;
	char		**tab;
	
}       t_data;

#endif
