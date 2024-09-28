/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/28 15:29:57 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_epure_line(char *str)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(char), ft_strlen(str) + 3);
	while (str[i])
	{
		while (str[i] && ft_iswite_space(str[i]))
			i++;
		if (str[i] && !ft_iswite_space(str[i]) && i != 0)
			new[j++] = ' ';
		while (str[i] && !ft_iswite_space(str[i]))
			new[j++] = str[i++];
	}
	return (new);
}

void	ft_add_name(char *, t_data *data)
{
	char		**tab;
	t_d_list	*list;
	int			i;

	tab = ft_split(data->input, "|");
	data->tab = tab;
	i = 0;
	list = NULL;
	while (tab[i])
	{
		ft_add_back_list(&(list), ft_newlist(tab[i]));
		i++;
	}
	data->pipe = i;
	data->list = list;
}

int	ft_tokenisation(t_data *data)
{
	t_d_list	*temp;

	ft_add_name(data->input, data);
	printf("%d\n", data->pipe);
	temp = *(&(data->list));
	while (temp)
	{
		ft_init_list(&(temp));
		temp->data = data;
		if (ft_is_heredoc(temp->token->name))
		{
			ft_heredoc(temp);
		}
		temp = temp->next;
	}
	free (data->tab);
	return (0);
}

int	get_input(t_data *data)
{
	char	*rd_line;

	rd_line = readline("😂😂😂😂$ ");
	if (!rd_line)
		return (1);
	data->input = ft_epure_line(rd_line);
	printf("[input] : %s\n", data->input);
	free (rd_line);
	if (ft_strncmp(data->input, "exit", 4) == 0)
		ft_exit (data, 2);
	ft_tokenisation(data);
	// while (ft_end_pip(data->input))
	// {
	// 	ft_free_loop(data, 0);
	// 	rd_line = readline("🥶🥶$ ");
	// 	data->input = ft_strjoin_2(data->input, rd_line);
	// 	ft_tokenisation(data);
	// }
	return (0);
}
