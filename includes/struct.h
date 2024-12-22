/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:44:23 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/20 20:33:37 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "../libft/libft.h"

typedef struct s_token	t_token;
typedef struct s_d_list	t_d_list;
typedef struct s_data	t_data;
typedef struct s_signal	t_signal;

typedef struct s_cmd
{
	int	is_cmd;
	int	is_dir;
}				t_cmd;

typedef struct s_token
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

typedef struct s_data
{
	t_list		*env;
	pid_t		pid;
	pid_t		last_pid;
	int			error;
	int			path;
	int			is_heredoc;
	int			return_value;
	int			i;
	char		*input;
	char		*prompt;
	char		*history;
	char		*old_pwd;
	char		*pwd;
	char		*heredoc;
	char		**tab;
	char		**keys;
	int			saved_fd;
	int			status;
	int			*checker;
	t_signal	*signal;
	t_d_list	*list;
	t_d_list	*temp_list;
}				t_data;

#endif
