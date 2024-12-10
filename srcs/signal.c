/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:14:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/04 13:48:53 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static t_data	*data;

	(void) info;
	if (data == NULL)
		data = (t_data *) context;
	if (sig == SIGINT)
	{
		printf("\n");
		data->error = 1;
	}
}

void	interupt(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	waiting_signal(t_data *data)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset((&sa.sa_mask));
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
	handler(0, NULL, data);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	t_data	*data;

	(void) info;
	data = (t_data *) context;
	if (sig == SIGINT || sig == SIGQUIT)
	{
		data->error = 1;
		if (sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		else if (sig == SIGINT || sig == SIGQUIT)
			printf("\n");
	}
}

void	signal_heredoc(t_data *data)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset((&s_sigaction.sa_mask));
	sigaction(SIGINT, &s_sigaction, NULL);
	sigaction(SIGQUIT, &s_sigaction, NULL);
	handler(0, NULL, data);
}
