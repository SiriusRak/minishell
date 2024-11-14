/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:54 by enarindr          #+#    #+#             */
/*   Updated: 2024/11/14 08:06:23 by enarindr         ###   ########.fr       */
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
	while (ft_isalnum(str[start + i]))
		i++;
	key = ft_substr(str, start, i);
	printf("key---%s\n", key);
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
	next = ft_substr(str, i + 1, ft_strlen(str));	
	free (str);
	*chn = ft_strjoin_2(prev, ft_strdup("$HOME"));
	*chn = ft_strjoin_2(*chn, next);
	return (i);
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
	next = ft_substr(str, i, ft_strlen(str));	
	prev = ft_strjoin_2(prev, value);
	free (str);
	*chn = ft_strjoin_2(prev,next);
	return(j);
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
	next = ft_substr(str, i, ft_strlen(str));	
	prev = ft_strjoin_2(prev, value);
	free (str);
	*chn = ft_strjoin_2(prev,next);
	return(j);
}

int	ft_expand_4(char **chn, int i, char *str)
{
	char	*prev;
	char	*next;

	prev = ft_substr(str, 0, i);
	next = ft_substr(str, i + 1, ft_strlen(str));
	free (str);
	*chn = ft_strjoin_2(prev, next);
	return(0);
}

int	ft_expand_return(t_d_list *list, char **chn, char *str, int i)
{
	char	*prev;
	char	*next;
	char	*value;

	prev = ft_substr(str, 0, i);
	value = ft_strdup(ft_itoa(list->data->return_value));
	i++;
	next = ft_substr(str, i + 1, ft_strlen(str));
	prev = ft_strjoin_2(prev, value);
	free(str);
	*chn = ft_strjoin_2(prev, next);
	return (i);
}

int	ft_expand(t_d_list *list, char **chn, int i, int quote)
{
	char	*str;

	str = *chn;
	if (str[i] == '~' && (!str[i + 1]
		|| str[i + 1] == '/') && i == 0)
		return (ft_expand_1(chn, i, str));
	if (str[i + 1] == '?')
		i = ft_expand_return(list, chn, str, i);
	else if (str[i] && str[i] == '$' && str[i + 1] &&
		!ft_isdigit(str[i + 1]) && str[i + 1] != ' ' && str[i + 1] != '~'
		&& ft_isalpha(str[i + 1]))
		return (ft_expand_2(list, chn, i, str));
	else if (str[i + 1] == '$')
		ft_expand_3(list, chn, i, str);
	else if (str[i + 1] && (ft_isalnum(str[i + 1])
		|| str[i + 1] == '\"' || str[i + 1] == '\'') && quote == 0)
		return (ft_expand_4(chn, i, str));
	return (1);
}

char	*ft_expand_here(t_d_list *list, char *ch)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(ch);
	free(ch);
	while (str[i])
	{
		if (str[i] == '$')
			i += ft_expand(list, &str, i, 0);
		else
			i++;
	}
	return (str);
}

char	*ft_clean_quote(t_d_list *list, char *str, int type)
{
	int		i;
	char	*prev;
	char	*next;
	char	c;
	int		quote;

	i = 0;
	quote = 0;
	while (str && str[i])
	{
		c = str[i];
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = 1;
			prev = ft_substr(str, 0, i);
			next = ft_substr(str, i + 1, ft_strlen(str));
			free (str);
			str = ft_strjoin_2(prev, next);
			while (str[i] && str[i] != c)
			{
				if (c == '\"' && str[i] == '$' && type != HERE)
					i+= ft_expand(list, &str, i, quote);
				else
					i++;
			}
			if (str[i] && str[i] == c)
			{
				quote = 1;
				prev = ft_substr(str, 0, i);
				next = ft_substr(str, i + 1, ft_strlen(str));
				free (str);
				str = ft_strjoin_2(prev, next);
			}
		}
		else if ((str[i] == '$' && type != HERE) || str[i] == '~')
			i += ft_expand(list, &str, i, 0);
		else
			i++;
	}
	return (str);
}
