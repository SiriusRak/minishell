/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:17:53 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/18 11:51:32 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_expand_key(t_d_list *list, char *str, int start)
{
	char	*key;
	char	*value;
	char	**tab;
	t_list	*env;
	int		i;

	i = 0;
	env = list->data->env;
	value = NULL;
	while (ft_isalnum(str[start + i]))
		i++;
	key = ft_substr(str, start, i);
	printf("key---%s\n", key);
	i = 0;
	while (env && ft_strncmp(key, ft_get_key(env->content), ft_strlen(env->content)) != 0)
		env = env->next;
	if (env && ft_strncmp(key, ft_get_key(env->content), ft_strlen(env->content)) == 0)
	{
		tab = ft_split(env->content, "=");
		value = tab[1];
		free (tab[0]);
		free (tab);
	}
	printf("value---%s\n", value);
	return (value);
}

int	ft_expand(t_d_list *list, char **chn, int i)
{
	char	*prev;
	char	*next;
	char	*value;
	char	*str;

	str = *chn;
	if (str[i] == '$' && !ft_isdigit(str[i + 1]) && ft_isalpha(str[i + 1]))
	{
		ft_strlcpy(&(str[i]), &(str[i + 1]), ft_strlen(str) - i + 1);
		value = ft_expand_key(list, str, i);
		prev = ft_substr(str, 0, i);
		while (ft_isalnum(str[i]))
			i++;
		next = ft_substr(str, i + 1, ft_strlen(str) - i);
		i += ft_strlen(value);
		prev = ft_strjoin_2(prev, value);
		free (str);
		*chn = ft_strjoin_2(prev, next);
	}
	return(i);
}

char	*ft_clean_quote(t_d_list *list, char *str, int type)
{
	int		i;
	char	*prev;
	char	*next;
	char	c;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			c = str[i];
			prev = ft_substr(str, 0, i);
			next = ft_substr(str, i + 1, ft_strlen(str) - i);
			free (str);
			str = ft_strjoin_2(prev, next);
			while (str[i] && str[i] != c)
			{
				if (c == '\"' && str[i] == '$' && type != HERE)
					i = ft_expand(list, &str, i);
				i++;
			}
			if (str[i] == c)
			{
				if (!str[i + 1])
					str[i] = '\0';
				else
				{
					prev = ft_substr(str, 0, i);
					next = ft_substr(str, i + 1, ft_strlen(str) - i);
					free (str);
					str = ft_strjoin_2(prev, next);
				}
			}
		}
		else if (str[i] && str[i] == '$' && type != HERE)
			i = ft_expand(list, &str, i);
		i++;
	}
	return (str);
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

int	ft_add_in(t_d_list *list, char *str, int i)
{
	t_list	*lst;

	if (!ft_check_error(str))
		return (1);
	if (i == HERE)
		// ft_add_heredok(list, str);
	str = ft_clean_quote(list, str, i);
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
