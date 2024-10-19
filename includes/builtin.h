/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:43:41 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/18 17:04:21 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

#ifndef BUILTIN_H
# define BUILTIN_H

void	ft_builtin_echo(char **arg);
void	ft_buitlin_cd(char **arg, t_data *data);
void	ft_builtin_exit(char **arg);
void	ft_builtin_pwd(void);
void	ft_builtin_env(t_data *data);
void    ft_builtin_export(char **key, t_data *data, char **args);
void    ft_builtin_unset(t_data *data, char **key);
void	ft_key_isexist(t_list *list, char **keys, char **args);
void	ft_addkey(t_list *list, char **keys, char **args);
void	ft_change_pwd(t_data *data, char **old_pwd, char **pwd, int i);
char	*ft_get_key(char *content);
char	**ft_get_allkey(t_list *list);
char	*ft_find_in_path(char *cmd);
int     ft_is_builtin(char *cmd);

#endif