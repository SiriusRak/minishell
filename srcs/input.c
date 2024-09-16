/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/16 15:15:28 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_input(char *s)
{
	printf("%ld\n", ft_strlen(s));
}

void	get_input(char **env)
{
	char	*input;

	input = readline("Minishell$ ");
	if (input == NULL)
		rl_redisplay();
	if (*input)
	{
		add_history(input);
		parse_input(input, env);
	}
    printf("%s\n", input);
	free(input);
}
