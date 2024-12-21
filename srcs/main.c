/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:55:15 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/21 11:18:56 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>

void	ft_write_in_history(char *str)
{
	int		fd;
	char	*home;

	home = getenv("HOME");
	home = ft_strjoin_2(ft_strdup(home), ft_strdup("/.mini_history"));
	fd = open(home, O_WRONLY | O_CREAT | O_APPEND, 0777);
	write(fd, "\n", 1);
	write(fd, str, ft_strlen(str));
	free (home);
	close (fd);
}

void	ft_add_history(void)
{
	int		fd;
	int		i;
	char	*home;
	char	*temp;
	char	**tab;

	i = 0;
	temp = NULL;
	home = getenv("HOME");
	home = ft_strjoin_2(ft_strdup(home), ft_strdup("/.mini_history"));
	fd = open(home, O_RDONLY);
	if (fd > 0)
		temp = take_script(fd);
	if (ft_strlen(temp))
	{
		tab = ft_split(temp, "\n");
		while (tab[i])
			add_history(tab[i++]);
		ft_free_tab(tab);
	}
	free (home);
	if (temp)
		free (temp);
	close(fd);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	ft_init(&data, env);
	ft_add_history();
	while (1)
	{
		data.error = 0;
		ft_get_input(&data);
		if (data.history && ft_strlen(data.history) > 0)
		{
			add_history(data.history);
			ft_write_in_history(data.history);
		}
		ft_clear_history(&data);
		ft_clear_input(&data);
	}
	return (0);
}
