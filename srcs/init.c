/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:26:35 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/07 08:27:22 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_init_list(t_d_list **list)
{
	(*list)->token->arg = NULL;
	(*list)->token->cmd = NULL;
	(*list)->token->in = NULL;
	(*list)->token->out = NULL;
	(*list)->token->var = NULL;
	(*list)->token->var_two = NULL;
	(*list)->token->heredoc = NULL;
}

int	ft_init(char **env, t_data *data)
{
	(void) env;
	data->env = ft_split(getenv("PATH"), ":");
	data->input = NULL;
	data->list = NULL;
	data->final_list = NULL;
	data->prompt = NULL;
	return (0);
}

char	*ft_epure_line(char *str)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(char), ft_strlen(str) + 3);
	while (str[i])
	{
		while (str[i] && ft_iswite_space(str[i]))
			i++;
		if (str[i] && !ft_iswite_space(str[i]) && i != 0)
			new[j++] = ' ';
		while (str[i] && !ft_iswite_space(str[i]))
			new[j++] = str[i++];
	}
	return (new);
}
