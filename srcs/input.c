/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:47:50 by enarindr          #+#    #+#             */
/*   Updated: 2024/11/07 20:33:46 by enarindr         ###   ########.fr       */
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
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = ft_find_next_quote(str, i, str[i], data);
			if (!i)
				return (0);
		}
		if (str[i] && str[i] == '|')
		{
			if (ft_pipe_error(str, i))
			{
				ft_exit_pipe(str, data);
				return (0);
			}
			i = ft_add_list(data, start, i, str);
			start = i + 1;
		}
		i++;
	}
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

int	ft_get_input(t_data *data)
{
	char	*rd_line;

	if (pipe(data->signal->fd) == -1)
		return 2;
	signal(SIGINT, SIG_IGN);
	data->signal->pid = fork();
	if (data->signal->pid == 0)
	{
		waiting_signial_here(data);
		close((data->signal->fd)[0]);
		rd_line = readline("MINISHELL $ ");
		if (!rd_line)
			rd_line = ft_strdup("exit");
		write((data->signal->fd)[1], rd_line, ft_strlen(rd_line));
		close((data->signal->fd)[1]);
		free (rd_line);
		ft_exit_child(data);
	}
	signal_heredoc(data);
	waitpid(data->signal->pid, &(data->signal->stats), 0);
	// if (WIFEXITED(data->signal->stats))
	// 	data->return_value = WEXITSTATUS(data->signal->stats);
	// if (WIFSIGNALED(data->signal->stats))
	// {
	// 	data->return_value = WTERMSIG(data->signal->stats) + 128;
	// 	data->error = 1;
	// }
	close((data->signal->fd)[1]);
	if (data->error == 1)
	{
		data->return_value = 130;
		return (130);
	}
	signal(SIGINT, SIG_IGN);
	waiting_signal(data);
	rd_line = take_script((data->signal->fd)[0]);
	if (!rd_line)
		return (0);
	close((data->signal->fd)[0]);
	if (ft_exit(rd_line))
		ft_exit_1(data);
	data->input = ft_strdup(rd_line);
	data->history = ft_strjoin_2(data->history, ft_strdup(rd_line));
	if (!ft_take_pipe(rd_line, data))
	{
		data->return_value = 2;
		return (2);
	}
	printf("HEOOO\n");
	if (!ft_check_list(data))
	{
		data->return_value = 2;
		return (2);
	}
	ft_add_back_list(&data->list, data->temp_list);
	data->temp_list = NULL;
	if (data->error == 1)
	{
		printf("atooo----\n");
		data->return_value = 130;
		return (130);
	}
	// while (ft_end_of_pipe(data->input))
	// {
	// 	data->error = 0;
	// 	ft_clear_input(data);
	// 	if (pipe(fd) == -1)
	// 		return 2;
	// 	pid = fork();
	// 	signal(SIGINT, SIG_IGN);
	// 	if (pid == 0)
	// 	{
	// 		close(fd[0]);
	// 		waiting_signial_here(data);
	// 		rd_line = readline("PiPe $ ");
	// 		if (!rd_line)
	// 		{
	// 			ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	// 			close(fd[1]);
	// 			ft_exit_1(data);
	// 		}
	// 		write(fd[1], rd_line, ft_strlen(rd_line));
	// 		close(fd[1]);
	// 		free (rd_line);
	// 		ft_exit_child(data);
	// 	}
	// 	signal_heredoc(data);
	// 	close(fd[1]);
	// 	wait(0);
	// 	waiting_signal(data);
	// 	ft_clear_input(data);
	// 	if (data->error == 1)
	// 	{
	// 		data->return_value = 130;
	// 		return (130);
	// 	}
	// 	rd_line = take_script(fd[0]);
	// 	if (!rd_line)
	// 		continue;
	// 	close (fd[0]);
	// 	data->input = ft_strdup(rd_line);
	// 	data->history = ft_strjoin_2(data->history, ft_strdup(" "));
	// 	data->history = ft_strjoin_2(data->history, ft_strdup(rd_line));
	// 	if (!ft_take_pipe(rd_line, data))
	// 		return (2);
	// 	if (!ft_check_list(data))
	// 		return (2);
	// 	ft_add_back_list(&data->list, data->temp_list);
	// 	data->temp_list = NULL;
	// 	if (data->error == 1)
	// 	{
	// 		data->return_value = 130;
	// 		return (130);
	// 	}
	// }
	ft_print_all(data);
	// ft_execute(data);
	return (0);
}
