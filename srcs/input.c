/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/25 14:55:46 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_tokenisation(t_data *data)
// {
// 	char		**tab;
// 	t_d_list	*list;
// 	int		i;

// 	i = 0;
// 	tab = ft_split(data->input, " ");
// 	list = NULL;
// 	while (tab[i])
// 	{
// 		ft_add_back_list(&list, ft_newlist(tab[i]));
// 		i++;
// 	}
// 	data->tab = tab;
// }

// void	ft_init_token(t_data *data)
// {
// 	t_d_list	*temp;

// 	temp = data->list;
// 	while (temp)
// 	{
// 		if (ft_is_builtin(temp))
// 			ft_make_build(temp);
// 		else if (ft_is_cmd(temp))
// 			ft_make_cmd(temp);
// 		else if (temp->token->name == "\\")
// 			ft_make_pipe(temp);
// 		else if (temp->token->name == ">>")
// 			ft_make_redir(temp);
// 	}
// }

void	parse_input(t_data *data)
{
	// printf("%ld\n", ft_strlen(data->input));
	// ft_tokenisation(data);
	// ft_init_token(data);
}

void	get_input(t_data *data)
{
	data->input = readline("Minishell$ ");
	if (data->input == NULL)
		rl_redisplay();
	if (data->input)
	{
		add_history(data->input);
		// parse_input(data);
		// ft_execute(data);
	}
}
