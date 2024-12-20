/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:42:56 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/20 19:59:17 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <time.h>

int	ft_lex_ext(t_d_list *list, char **tab, int i)
{
	int		error;

	if (tab[i + 1])
	{
		error = ft_lex_ext2(list, tab, i);
		if (error == 1)
		{
			list->data->return_value = 2;
			while (tab[++i])
				free(tab[i]);
		}
		return (error);
	}
	else
	{
		ft_putstr_fd("MINISHELL: syntax error near unexpected\
token `newline'\n", 2);
		list->data->return_value = 2;
		return (1);
	}
	return (0);
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
			free(tab[i]);
			tab[i] = NULL;
			++i;
		}
		else
			error = ft_add_cmd(list, tab[i]);
		if (error == 1)
		{
			free(tab);
			list->data->tab = NULL;
			return (0);
		}
	}
	free(tab);
	list->data->tab = NULL;
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
