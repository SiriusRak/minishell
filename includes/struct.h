/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:44:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/25 12:41:43 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#ifndef STRUCT_H
# define STRUCT_H

typedef	struct	s_type	t_type;
typedef struct s_token	t_token;
typedef struct s_d_list	t_d_list;
typedef struct  s_data	t_data;

typedef	struct s_token
{
	t_list	*cmd;
	t_list	*builting;
	t_list	*arg;
	t_list	*in;
	t_list	*out;
	t_list	*heredoc;
	t_list	*var;
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
	t_list		*env;
	char		**tab;
	char		*input;
	char		*sep;
	t_d_list	*list;
}				t_data;

#endif
