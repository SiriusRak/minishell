/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:19:00 by enarindr          #+#    #+#             */
/*   Updated: 2024/09/28 08:57:34 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_is_heredoc(char	*str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

void	ft_add_file(char *file, t_data *data)
{
	char	*heredoc;
	char	*text;

	text = NULL;
	while (1)
	{
		heredoc = readline("👉 ");
		if (!heredoc)
		{
			if (text)
				free (text);
			ft_exit(data, 1);
		}
		if (ft_strncmp(file, heredoc, ft_strlen(heredoc)) == 0
			&& ft_strlen(file) == ft_strlen(heredoc))
		{
			ft_lstadd_back(&(data->list->token->heredoc), ft_lstnew(text));
			free (file);
			free (heredoc);
			return ;
		}
		if (text)
			heredoc = ft_strjoin_2(ft_strdup("\n"), heredoc);
		text = ft_strjoin_2(text, heredoc);
	}
}

void	ft_add_heredoc(t_data *data, int start, int pip)
{
	int			i;
	int			begin;
	char		*file;
	t_d_list	*list;

	i = 0;
	begin = 0;
	file = ft_calloc(sizeof(char), ft_strlen(data->input) + 1);
	if (!file)
		return ;
	if (data->input[start] == ' ')
		start++;
	while (data->input[start] && ft_notsep(data->input[start], data))
		file[i++] = data->input[start++];
	file[i] = '\0';
	while (begin < pip)
	{
		list = list->next;
		begin++;
	}
	ft_add_file(file, data);	
}

void	ft_heredoc(t_data *data)
{
	int		pip;
	int		i;

	pip = 0;
	i = 0;
	while (data->input[i + 1])
	{
		if (data->input[i] == '<' && data->input[i + 1] == '<')
		{
			i += 2;
			ft_add_heredoc(data, i, pip);
			while (data->input[i] && ft_notsep(data->input[i], data))
				i++;
		}
		i++;
	}
	/***print heredoc****/
	ft_print_list(&(data->list->token->heredoc));
}
