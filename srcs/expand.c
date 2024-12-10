/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:54 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/08 11:29:47 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_expand_key(t_d_list *list, char *str, int start)
{
	t_list	*env;
	char	*value;
	char	*key;
	int		i;

	i = 0;
	env = list->data->env;
	while (str[start + i] && ft_isalnum(str[start + i]))
		i++;
	key = ft_substr(str, start, i);
	i = 0;
	if (key[0] == '?' && ft_strlen(key) == 1)
		value = ft_strdup(ft_itoa(list->data->return_value));
	else
		value = ft_get_value(key, env);
	free (key);
	return (value);
}

int	ft_expand_1(char **chn, int i, char *str)
{
	char	*prev;
	char	*next;

	prev = ft_substr(str, 0, i);
	i++;
	if (str[i])
		next = ft_substr(str, i, ft_strlen(str));
	else
		next = NULL;
	free (*chn);
	*chn = ft_strjoin_2(prev, ft_strdup("$HOME"));
	*chn = ft_strjoin_2(*chn, next);
	return (i - 1);
}

int	ft_expand_2(t_d_list *list, char **chn, int i, char *str)
{
	char	*prev;
	char	*next;
	char	*value;
	int		j;

	prev = ft_substr(str, 0, i);
	value = ft_expand_key(list, str, i + 1);
	j = ft_strlen(value);
	i++;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (str[i])
		next = ft_substr(str, i, ft_strlen(str));
	else
		next = NULL;
	prev = ft_strjoin_2(prev, value);
	free (*chn);
	*chn = ft_strjoin_2(prev, next);
	return (j);
}

int	ft_expand_3(t_d_list *list, char **chn, int i, char *str)
{
	char	*prev;
	char	*next;
	char	*value;
	int		j;

	prev = ft_substr(str, 0, i);
	value = ft_itoa(list->data->pid);
	j = ft_strlen(value);
	i += 2;
	if (str[i])
		next = ft_substr(str, i, ft_strlen(str));
	else
		next = NULL;
	prev = ft_strjoin_2(prev, value);
	free (str);
	*chn = ft_strjoin_2(prev, next);
	return (j);
}

int	ft_expand_4(char **chn, int i, char *str, int quote)
{
	char	*prev;
	char	*next;

	prev = NULL;
	next = NULL;
	if (!str[i + 1] || (quote == 1 && (str[i + 1] == '\''
				|| str[i + 1] == '\"')))
	{
		prev = ft_substr(str, 0, i + 1);
		i++;
	}
	else
		prev = ft_substr(str, 0, i);
	if (quote == 0 && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		next = (ft_substr(str, i + 1, ft_strlen(str)));
	else if (str[i] && str[i + 1] && ft_isdigit(str[i + 1]))
		next = ft_substr(str, i + 2, ft_strlen(str));
	else if (str[i] && str[i + 1])
		next = (ft_substr(str, i, ft_strlen(str)));
	free (*chn);
	*chn = ft_strjoin_2(prev, next);
	return (i);
}
