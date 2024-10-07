/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:19:00 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/07 07:23:05 by enarindr         ###   ########.fr       */
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

void	ft_add_file(char *file, t_d_list *list)
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
			ft_exit(list->data, 1);
		}
		if (ft_strncmp(file, heredoc, ft_strlen(heredoc)) == 0
			&& ft_strlen(file) == ft_strlen(heredoc))
		{
			ft_lstadd_back(&(list->token->heredoc), ft_lstnew(text));
			free (file);
			free (heredoc);
			return ;
		}
		if (text)
			heredoc = ft_strjoin_2(ft_strdup("\n"), heredoc);
		text = ft_strjoin_2(text, heredoc);
	}
}

void	ft_add_heredoc(t_d_list *list, int start, int pip)
{
	int			i;
	char		*file;

	i = 0;
	(void) pip;
	file = ft_calloc(sizeof(char), ft_strlen(list->token->name) + 1);
	if (!file)
		return ;
	if (list->token->name[start] == ' ')
		start++;
	while (list->token->name[start] && ft_notsep(list->token->name[start]))
		file[i++] = list->token->name[start++];
	file[i] = '\0';
	ft_add_file(file, list);	
}

void	ft_heredoc(t_d_list *list)
{
	int		pip;
	int		i;

	pip = 0;
	i = 0;
	list->token->type = HERE;
	while (list->token->name[i + 1])
	{
		if (list->token->name[i] == '<' && list->token->name[i + 1] == '<')
		{
			i += 2;
			ft_add_heredoc(list, i, pip);
			while (list->token->name[i] && ft_notsep(list->token->name[i]))
				i++;
		}
		i++;
	}
	/***print heredoc****/
	ft_print_list(&(list->token->heredoc));
}
