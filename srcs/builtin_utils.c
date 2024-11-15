/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:04:22 by rdiary            #+#    #+#             */
/*   Updated: 2024/11/15 10:47:57 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_key(char *content)
{
	char	*key;
	int		i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, content, i + 1);
	return (key);
}

char	*ft_get_value(char *key, t_list *env)
{
	char	*value;
	char	**tab;
	char	*key_2;

	value = NULL;
	key_2 = ft_get_key(env->content);
	if (key_2)
	{
		while (env && (ft_strncmp(key, key_2, ft_strlen(key))!= 0
			|| ft_strncmp(key, key_2, ft_strlen(key_2))!= 0))
		{
			free (key_2);
			key_2 = NULL;
			env = env->next;
			if (env)
				key_2 = ft_get_key(env->content);
		}
		if (env && ft_strncmp(key, key_2, ft_strlen(key))== 0
			&& ft_strlen(key) == ft_strlen(key_2))
		{
			tab = ft_split(env->content, "=");
			value = ft_strdup(tab[1]);
			ft_free_tab(tab);
		}
		if (key_2)
			free(key_2);
	}
	return (value);
}

char	**ft_get_allkey(t_list *list)
{
	char	**keys;
	t_list	*tmp;
	int		i;

	i = 0;
	keys = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	tmp = list;
	tmp = tmp->next;
	while (tmp)
	{
		keys[i++] = ft_get_key(tmp->content);
		tmp = tmp->next;
	}
	keys[i] = 0;
	return (keys);
}

char	**ft_lst_to_char(t_list *list, int type)
{
	char	**tab;
	int		i;
	t_list	*tmp;

	tmp = list;
	tab = malloc ((ft_lstsize(list) + 1) * sizeof(char *));
	if (!tab)
	{
		perror("malloc");
		return (NULL);
	}
	if (type == 1)
		tmp = tmp->next;
	i = 0;
	while (tmp)
	{
		tab[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	ft_key_isexist(t_list *list, char **keys, char **args)
{
	int	i;

	i = 0;
	while (i < ft_count_line(keys))
	{
		if (ft_strncmp(list->content, keys[i], ft_strlen(keys[i])) == 0)
		{
			free(list->content);
			list->content = ft_strdup(args[i]);
		}
		i++;
	}
}

void	ft_addkey(t_list *list, char **keys, char **args)
{
	int		is_exist;
	int		i;
	t_list	*tmp;

	tmp = list;
	i = 0;
	while (i < ft_count_line(keys))
	{
		printf("%s\n", args[i]);
		is_exist = 0;
		while (list)
		{
			if (!ft_strncmp(list->content, keys[i], ft_strlen(keys[i])))
				is_exist = 1;
			list = list->next;
		}
		list = tmp;
		if (!is_exist)
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(args[i])));
		i++;
	}
}
