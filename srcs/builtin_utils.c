/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:04:22 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/27 13:44:38 by rdiary           ###   ########.fr       */
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
	while (key[i])
	{
		key[i] = ft_toupper(key[i]);
		i++;
	}
	return (key);
}

char	**ft_lstcopy(t_list *list)
{
	char	**tab;
	int		i;
	t_list	*tmp;

	tmp = list;
	tab = malloc (ft_lstsize(list) * sizeof(char *));
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
	tab[i] = 0;
	return (tab);
}
