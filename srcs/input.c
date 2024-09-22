/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/22 17:14:58 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_notsep(char	c, t_data *data)
{
	int		i;

	i = 0;
	while (data->sep[i])
	{
		if (data->sep[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_init_list(t_d_list *list)
{
	list->token->arg = NULL;
	list->token->cmd = NULL;
	list->token->heredoc = NULL;
	list->token->in = NULL;
	list->token->out = NULL;
	list->token->out_two = NULL;
	list->token->var = NULL;
}
int		ft_quotes(t_d_list *list, int start)
{
	int		len;
	int		i;

	i = start + 1;
	while (list->token->name[i] != '\'' && list->token->name[i] != '\"')
		list->token->name[i++];
	len = i - start + 2;
}

void	ft_parse(t_d_list *list, t_data *data)
{
	int	i;

	i = 0;
	ft_init_list(list);
	while (list->token->name[i])
	{
		if (list->token->name[i] == '\''
			&& list->token->name[i] == '\"')
			i += ft_quotes(list, i);
	}
	
}

void	ft_tokenisation(t_data *data)
{
	int			start;
	int			len;
	t_d_list	*temp;

	start = 0;
	temp = data->list;
	while (temp)
	{
		ft_parse(temp, data);
		temp = temp->next;
	}
}

void	ft_make_list(t_data *data)
{
	int	i;

	i = 0;
	while (data->tab[i])
	{
		ft_add_back_list(&data->list, ft_newlist(data->tab[i]));
		i++;
	}
}

void	parse_input(t_data *data)
{
	printf("%ld\n", ft_strlen(data->input));
	data->tab = ft_split(data->input, "|");
	ft_make_list(data);
	ft_tokenisation(data);
}

void	get_input(t_data *data)
{
	data->input = readline("Minishell$ ");
	if (data->input)
	{
		add_history(data->input);
		parse_input(data);
	}
}
