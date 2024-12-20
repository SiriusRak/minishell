/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:49:06 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/20 21:12:39 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <time.h>

void	signal_handler_cmd(int sig, siginfo_t *info, void *context)
{
	static t_data	*data;

	(void) info;
	data = (t_data *) context;
	if (sig == SIGINT || sig == SIGQUIT)
	{
		data->error = 1;
		write(2, "\n", 1);
		ft_lstclear_2(&(data->env));
		ft_clear_history(data);
		ft_clear_input(data);
		ft_free_data(data);
		clear_history();
		exit(sig + 128);
	}
}

void	waiting_signial_cmd(t_data *data)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = signal_handler_cmd;
	s_sigaction.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset((&s_sigaction.sa_mask));
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGQUIT, &s_sigaction, NULL);
	signal_handler_cmd(0, NULL, data);
}

int		free_here_tab(t_data * data)
{
	if (data->tab)
	{
		while (data->tab[data->i])
		{
			free (data->tab[(data->i)]);
			data->tab[(data->i)++] = NULL;
		}
		free (data->tab);
	}
	if (data->heredoc)
	{
		free(data->heredoc);
		data->heredoc = NULL;
	}
	return (0);
}

void	signal_handler_here(int sig, siginfo_t *info, void *context)
{
	static t_data	*data;

	(void) info;
	if (data == NULL)
	{
		data = (t_data *) context;
		data->error = 1;
	}
	if (sig == SIGINT)
	{
		close(data->signal->fd[0]);
		close(data->signal->fd[1]);
		ft_lstclear_2(&(data->env));
		ft_clear_history(data);
		ft_clear_input(data);
		if (data->temp_list)
			ft_free_t_d_list(data->temp_list);
		free_here_tab(data);
		ft_free_data(data);
		clear_history();
		free (data->signal);
		exit(sig + 128);
	}
}

void	waiting_signial_here(t_data *data)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = signal_handler_here;
	s_sigaction.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset((&s_sigaction.sa_mask));
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &s_sigaction, NULL);
	signal_handler_here(0, NULL, data);
}
