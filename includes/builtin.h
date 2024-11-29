/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:43:41 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/28 16:48:39 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

#ifndef BUILTIN_H
# define BUILTIN_H

void	ft_restore_fd(t_data *data, int saved_fd);
void	ft_key_isexist(t_list *list, char **keys, char **args);
void	ft_addkey(t_list *list, char **keys, char **args);
void	ft_change_pwd(t_data *data, char **old_pwd, char **pwd, int i);
char	*ft_get_key(char *content);
char	**ft_get_allkey(t_list *list);
char	*ft_find_in_path(char *cmd);
int		ft_builtin_echo(char **arg);
int		ft_buitlin_cd(char **arg, t_data *data);
int		ft_builtin_exit(t_data *data, char **arg);
int		ft_builtin_pwd(void);
int		ft_builtin_env(t_data *data);
int		ft_builtin_export(char **key, t_data *data, char **args);
int		ft_builtin_unset(t_data *data, char **key);
int		ft_is_builtin(char *cmd);
int		ft_check_arg(char *arg, int *newline);
int		ft_manage_unset(char *key, t_list *curr, t_list *prev, t_data *data);
int		ft_check_num(char *arg);
int     ft_check_key(char *key);
int     ft_check_allkey(char **keys);

#endif