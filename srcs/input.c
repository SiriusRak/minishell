/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/10 14:20:20 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_input(char *s)
{
	char	**input;

	input = ft_split(s, ' ');
	
	ft_free_split(input, ft_count_word(s, ' '));
}

void	get_input(void)
{
	char	*input;

	input = readline("Minishell$ ");
	if (input == NULL)
		rl_redisplay();
	if (*input)
	{
		add_history(input);
		parse_input(input);
	}
	free(input);
}
