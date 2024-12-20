/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:17:53 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/20 20:35:39 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	write_error(char *str)
{
	ft_putstr_fd("minishell: warning: here-document at line 1 delimi\
ted by end-of-file (wanted `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
}

char	*ft_add_heredoc(t_d_list *list, char *str, int c)
{
	char	*here;
	char	*temp;
	int		i;

	i = 0;
	here = NULL;
	temp = readline("here > ");
	if (!temp)
		write_error(str);
	while (temp != NULL && (ft_strncmp(temp, str, ft_strlen(str)) != 0
			|| ft_strncmp(temp, str, ft_strlen(temp)) != 0))
	{
		if (temp && c == 0)
			temp = ft_expand_here(list, temp);
		temp = ft_strjoin_2(temp, ft_strdup("\n"));
		list->data->heredoc = temp;
		here = ft_strjoin_2(here, temp);
		list->data->heredoc = here;
		temp = readline("here > ");
		if (!temp)
			write_error(str);
		i++;
	}
	if (temp)
		free (temp);
	return (here);
}

int	ft_add_out(t_d_list *list, char *str, int i)
{
	t_list	*lst;

	if (!ft_check_error(str))
	{
		list->data->return_value = 2;
		return (1);
	}
	str = ft_clean_quote(list, str, i);
	lst = ft_lstnew(ft_strdup(str));
	lst->type = i;
	ft_lstadd_back(&(list->token->out), lst);
	return (0);
}

void	ft_add_file(char *content, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	write(fd, content, ft_strlen(content));
	close (fd);
}
