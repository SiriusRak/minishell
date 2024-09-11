/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/10 13:11:46 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_input(char *s)
{
	printf("%ld\n", ft_strlen(s));
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
    printf("%s\n", input);
	free(input);
}
