/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/17 08:26:41 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tokenisation(t_data *data)
{
	char		**tab;
	t_d_list	*list;
	int		i;

	i = 0;
	tab = ft_split(data->input, " ");
	list = NULL;
	while (tab[i])
	{
		ft_add_back_list(&list, ft_newlist(tab[i]));
		i++;
	}
	data->tab = tab;
}

void	ft_init_token(t_d_list *list)
{
	t_d_list	*temp;

	temp = list;
	while (temp)
	{
		if (ft_is_builtin(temp))
			ft_make_build(temp);
		else if (ft_is_cmd(temp))
			ft_make_cmd(temp);
		else if (temp->token->name == "\\")
			ft_make_pipe(temp);
		else if (temp->token->name == ">>")
			ft_make_redir(temp);
	}
}

void	parse_input(t_data *data)
{
	printf("%ld\n", ft_strlen(data->input));
	ft_tokenisation(data);
	ft_init_token(data->list);
}

void	get_input(t_data *data)
{
	char	*input;

	input = readline("Minishell$ ");
	if (input == NULL)
		rl_redisplay();
	data->input = input;
	if (*input)
	{
		add_history(data->input);
		parse_input(data);
	}
    printf("%s\n", input);
	free(input);
}
