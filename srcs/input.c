/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:47:50 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/04 14:04:30 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int	ft_take_pipe(char *str, t_data *data)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	str = ft_epure_line(str, 0, 0);
	if (!str)
		return (0);
	if (str[0] && str[0] == '|')
	{
		ft_exit_pipe(str, data);
		return (0);
	}
	if (str[i])
		i = ft_take_pipe_ext(data, i, str, &start);
	if (i < 0)
		return (0);
	if (start < i)
		ft_add_list(data, start, i, str);
	free(str);
	return (1);
}

int	ft_end_of_pipe(char *str)
{
	if (str[ft_strlen(str) - 1] == '|')
		return (1);
	return (0);
}

char	*take_script(int fd)
{
	char	*str;
	char	*temp;

	str = NULL;
	temp = get_next_line(fd);
	str = ft_strjoin_2(str, temp);
	while (temp)
	{
		temp = get_next_line(fd);
		str = ft_strjoin_2(str, temp);
	}
	return (str);
}

int	ft_end_pipe(t_data *data)
{
	int	i;

	while (ft_end_of_pipe(data->input))
	{
		data->error = 0;
		ft_clear_input(data);
		if (pipe(data->signal->fd) == -1)
			return (2);
		signal(SIGINT, SIG_IGN);
		data->signal->pid = fork();
		if (data->signal->pid == 0)
			ft_pipe(data);
		check_after_child(data);
		close((data->signal->fd)[1]);
		if (ft_chek_sig(data))
			return (130);
		waiting_signal(data);
		i = pre_treat(data, 1);
		if (i == 130 || i == 2)
			return (i);
	}
	return (0);
}

int	ft_get_input(t_data *data)
{
	if (pipe(data->signal->fd) == -1)
		return (2);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	data->signal->pid = fork();
	if (data->signal->pid == 0)
		ft_readline(data);
	check_after_child(data);
	close((data->signal->fd)[1]);
	if (ft_chek_sig(data))
		return (130);
	if (pre_treat(data, 0))
		return (2);
	if (ft_end_pipe(data))
		return (2);
	ft_execute(data);
	return (0);
}
