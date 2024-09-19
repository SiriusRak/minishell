/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitlin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:43:41 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/19 14:18:50 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

#ifndef BUILTIN_H
# define BUILTIN_H

void	ft_builtin_echo(char *arg);
void	ft_buitlin_cd(char *arg);
void	ft_builtin_exit(char *arg);
void	ft_builtin_pwd(void);
void	ft_builtin_env(t_data *data);

#endif