/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:04:22 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/16 14:59:39 by rdiary           ###   ########.fr       */
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
	ft_strlcpy(key, content, i + 1);
	i = 0;
	return (key);
}

char	**ft_get_allkey(t_list *list)
{
	char	**keys;
	t_list	*tmp;
	int		i;

	i = 0;
	keys = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	tmp = list;
	while (tmp)
	{
		keys[i++] = ft_get_key(tmp->content);
		tmp = tmp->next;
	}
	keys[i] = 0;
	return (keys);
}

char	**ft_lst_to_char(t_list *list)
{
	char	**tab;
	int		i;
	t_list	*tmp;

	tmp = list;
	tab = malloc ((ft_lstsize(list)) * sizeof(char *));
	if (!tab)
	{
		perror("malloc");
		return (NULL);
	}
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
		is_exist = 0;
		while (list)
		{
			if (!ft_strncmp(list->content, keys[i], ft_strlen(keys[i])))
				is_exist = 1;
			list = list->next;
		}
		list = tmp;
		if (!is_exist)
			ft_lstadd_back(&list, ft_lstnew(args[i]));
		i++;
	}
}
