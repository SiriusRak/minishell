/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:17:53 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/24 13:28:04 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (temp && c == 0)
		temp = ft_expand_here(list, temp);
	while (temp != NULL && (ft_strncmp(temp, str, ft_strlen(str)) != 0
		|| ft_strlen(temp) != ft_strlen(str)))
	{
		if (i > 0)
			here = ft_strjoin_2(here, ft_strdup("\n"));
		here = ft_strjoin_2(here, temp);
		temp = readline("here > ");
		if (!temp)
			write_error(str);
		if (temp && c == 0)
			temp = ft_expand_here(list, temp);
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
		return (1);
	str = ft_clean_quote(list, str, i);
	lst = ft_lstnew(str);
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

int		ft_check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	fork_heredoc(t_d_list *list, char *str, char c)
{
	char	*here;

	waiting_signial_here(list->data);
	here = ft_add_heredoc(list, str, c);
	if (here)
	{
		ft_add_file(here,str);
		list->data->history = ft_strjoin_2(list->data->history, here);
	}
	exit(0);
}

int	ft_add_in(t_d_list *list, char *str, int i)
{
	t_list	*lst;
	int		c;
	int		pid;

	if (!ft_check_error(str))
		return (1);
	c = ft_check_quote(str);
	str = ft_clean_quote(list, str, i);
	if (i == HERE)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
			fork_heredoc(list, str, c);
		signal_heredoc(list->data);
	}
	lst = ft_lstnew(str);
	lst->type = i;
	ft_lstadd_back(&(list->token->in), lst);
	return (0);
}

int	ft_add_cmd(t_d_list *list, char *str)
{
	t_list	*lst;
	str = ft_clean_quote(list, str, 0);
	lst = ft_lstnew(str);
	if (!list->token->cmd)
		lst->type = CMD;
	else
		lst->type = ARG;
	ft_lstadd_back(&(list->token->cmd), lst);
	return (0);
}
