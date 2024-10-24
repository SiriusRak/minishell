/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:44:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/24 20:14:27 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#ifndef STRUCT_H
# define STRUCT_H

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
	pid_t		pid;
	int			error;
	int			return_value;
	char		*input;
	char		*prompt;
	char		*history;
	char		*old_pwd;
	char		*pwd;
	int			saved_fd;
	t_d_list	*list;
	t_d_list	*temp_list;
}				t_data;

#endif
