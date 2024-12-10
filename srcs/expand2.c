/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:23:13 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/08 11:23:34 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_expand_return(t_d_list *list, char **chn, char *str, int i)
{
	char	*prev;
	char	*next;
	char	*value;

	prev = ft_substr(str, 0, i);
	value = ft_itoa(list->data->return_value);
	i++;
	if (str[i + 1])
		next = ft_substr(str, i + 1, ft_strlen(str));
	else
		next = NULL;
	prev = ft_strjoin_2(prev, value);
	free(str);
	*chn = ft_strjoin_2(prev, next);
	return (i);
}

int	ft_expand(t_d_list *list, char **chn, int i, int quote)
{
	char	*str;

	(void) quote;
	str = *chn;
	if (str[i] == '~' && (!str[i + 1]
			|| str[i + 1] == '/') && i == 0)
		return (ft_expand_1(chn, i, str));
	str = *chn;
	if (str[i + 1] == '?')
		return (ft_expand_return(list, chn, str, i));
	else if (str[i + 1] && str[i] == '$' && ft_isalpha(str[i + 1]))
		return (ft_expand_2(list, chn, i, str));
	else if (str[i + 1] == '$')
		ft_expand_3(list, chn, i, str);
	else if (!str[i + 1] || ft_isdigit(str[i + 1])
		|| str[i + 1] == '\"' || str[i + 1] == '\'')
		return (ft_expand_4(chn, i, str, quote));
	else
		i++;
	return (i);
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

int	ft_clean(t_d_list **list, char **str, int i, int type)
{
	char	*prev;
	char	*next;
	int		quote;
	char	c;

	quote = 1;
	c = (*str)[i];
	prev = ft_substr(*str, 0, i);
	if ((*str)[i + 1])
		next = ft_substr(*str, i + 1, ft_strlen(*str));
	else
		next = NULL;
	free (*str);
	*str = ft_strjoin_2(prev, next);
	while ((*str)[i] && (*str)[i] != c)
	{
		if (c == '\"' && (*str)[i] == '$' && type != HERE)
			i = ft_expand(*list, str, i, quote);
		else
			i++;
	}
	return (i);
}

char	*ft_clean_ext(char *str, int i)
{
	char	*prev;
	char	*next;

	prev = ft_substr(str, 0, i);
	if (str[i + 1])
		next = ft_substr(str, i + 1, ft_strlen(str));
	else
		next = NULL;
	free (str);
	str = ft_strjoin_2(prev, next);
	return (str);
}
