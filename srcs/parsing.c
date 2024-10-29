/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:42:56 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/24 14:58:07 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lex_ext(t_d_list *list, char **tab, int i)
{
	int		error;
	int		signal_return;

	error = 0;
	if (tab[i + 1])
	{
		if (tab[i][0] == '>' && ft_strlen(tab[i]) == 1)
			error = ft_add_out(list, tab[i + 1], OUT);
		else if (tab[i][0] == '>' && tab[i][1] == '>')
			error = ft_add_out(list, tab[i + 1], OUT_2);
		else if (tab[i][0] == '<' && ft_strlen(tab[i]) == 1)
			error = ft_add_in(list, tab[i + 1], IN);
		else if (tab[i][0] == '<' && tab[i][1] == '<')
			error = ft_add_in(list, tab[i + 1], HERE);
		if (error == 1)
		{
			while (tab[++i])
				free(tab[i]);
		}
		return (error);
	}
	else
	{
		waitpid(0, &signal_return, 0);
		ft_putstr_fd("MINISHELL: syntax error near unexpected\
token `newline'\n", 2);
		return  (1);
	}
	return (1);
}

int	ft_lex(t_d_list *list, char *str)
{
	char	**tab;
	int		i;
	int		error;

	i = -1;
	tab = ft_split(str, "\n");
	free (str);
	while (tab[++i])
	{
		if (tab[i][0] == '<' || tab[i][0] == '>')
		{
			error = ft_lex_ext(list, tab, i);
			free (tab[i]);
			++i;
		}
		else
			error = ft_add_cmd(list, tab[i]);
		if (error == 1)
		{
			free (tab);
			return (0);
		}
	}
	free (tab);
	return (1);
}

int	ft_pars_ext(char *str, char **tmp, int i, char c)
{
	char	*temp;

	temp = *tmp;
	temp[i] = str[i];
	i++;
	while (str[i] != c)
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = str[i];
	i++;
	return (i);
}

int	ft_pars(t_d_list *list)
{
	int		i;
	char	*str;
	char	*temp;

	str = list->token->name;
	i = 0;
	temp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'')
			i = ft_pars_ext(str, &temp, i, '\'');
		else if (str[i] == '\"')
			i = ft_pars_ext(str, &temp, i, '\"');
		else if (str[i] == ' ')
			temp[i++] = '\n';
		else
		{
			temp[i] = str[i];
			i++;
		}
	}
	temp[i] = '\0';
	if (!ft_lex(list, temp))
		return (0);
	return (1);
}

int	ft_check_list(t_data *data)
{
	t_d_list	*list;
	int			signal_value;

	list = data->temp_list;
	while (list)
	{
		list->token->name = ft_epure_line(list->token->name, 0, 0);
		list->token->name =  ft_epure_space(list->token->name, 0, 0);
		list->token->name = ft_epure_redir(list->token->name);
		if (!ft_pars(list))
		{
			waitpid(0, &signal_value, 0);
			waiting_signal(data);
			return (signal_value);
		}
		wait(0);
		waiting_signal(data);
		list = list->next;
	}
	return (1);
}
