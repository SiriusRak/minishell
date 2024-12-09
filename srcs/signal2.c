/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:49:06 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/09 08:25:44 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
