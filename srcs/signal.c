/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:14:27 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/07 20:24:45 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int	sig, siginfo_t *info, void *context)
{
	static t_data	*data;

	(void) info;
	if (data == NULL)
	{
		data = (t_data *) context;
		data->return_value = 130;
	}
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		data->error = 1;
	}
}

void	interupt ()
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
	handler(0, NULL,  data);
}

void	signal_handler_here(int	sig, siginfo_t *info, void *context)
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
		write(2, "\n", 1);
		ft_lstclear_2(&(data->env));
		ft_free_tab(data->path);
		ft_clear_history(data);
		ft_clear_input(data);
		ft_free_data(data);
		clear_history();
		exit (130);
	}
}

void	handler(int	sig, siginfo_t *info, void *context)
{
	t_data	*data;

	(void) info;
	data = (t_data *) context;
	if (sig == SIGINT)
	{
		data->error = 1;
	}
}

void	signal_heredoc(t_data *data)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset((&s_sigaction.sa_mask));
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &s_sigaction, NULL);
	handler(0, NULL,  data);
}

void	waiting_signial_here(t_data *data)
{
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = signal_handler_here;
	s_sigaction.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset((&s_sigaction.sa_mask));
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &s_sigaction, NULL);
	signal_handler_here(0, NULL,  data);
}
