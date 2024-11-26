/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:44:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/26 07:32:59 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#ifndef STRUCT_H
# define STRUCT_H

// typedef	struct	s_type	t_type;
typedef struct s_token	t_token;
typedef struct s_d_list	t_d_list;
typedef struct  s_data	t_data;
typedef struct s_signal t_signal;

typedef struct s_cmd
{
	int	is_cmd;
	int	is_dir;
}				t_cmd;

typedef	struct s_token
{
	t_list	*cmd;
	t_list	*in;
	t_list	*out;
	char	*name;
	char	*path;
}				t_token;

typedef struct s_signal
{
	int		pid;
	int		fd[2];
	int		stats;
}				t_signal;

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
	int			is_heredoc;
	int			return_value;
	char		*input;
	char		*prompt;
	char		*history;
	char		*old_pwd;
	char		*pwd;
	int			saved_fd;
	t_signal	*signal;
	t_d_list	*list;
	t_d_list	*temp_list;
}				t_data;

#endif
