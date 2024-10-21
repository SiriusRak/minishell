/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:44:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/21 10:54:18 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#ifndef STRUCT_H
# define STRUCT_H
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
	char	*path;
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
	t_list		*env;
	char		**path;
	char		*input;
	char		*prompt;
	char		*history;
	char		*old_pwd;
	char		*pwd;
	int			saved_fd;
	t_d_list	*list;
}				t_data;

#endif
