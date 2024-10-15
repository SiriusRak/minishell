/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:17:53 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/15 17:37:29 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*ft_clear_word(char *str)
// {
// 	if (str[0] == '\"')
// 	{
		
// 	}
// }

int	ft_add_out(t_d_list *list, char *str, int i)
{
	t_list	*lst;

	if (!ft_check_error(str))
		return (1);
	// str = ft_clear_words(str);
	lst = ft_lstnew(str);
	if (i == 1)
		lst->type = OUT;
	else if (i == 2)
		lst->type = OUT_2;
	ft_lstadd_back(&(list->token->out), lst);
	return (0);
}

int	ft_add_in(t_d_list *list, char *str, int i)
{
	t_list	*lst;
	if (!ft_check_error(str))
		return (1);
	// str = ft_clear_words(str);
	lst = ft_lstnew(str);
	if (i == 1)
		lst->type = IN;
	else if (i == 2)
	{
		lst->type = HERE;
		// ft_add_heredok(list, str);
	}
	ft_lstadd_back(&(list->token->in), lst);
	return (0);
}

int	ft_add_cmd(t_d_list *list, char *str)
{
	t_list	*lst;
	// str = ft_clear_words(str);
	lst = ft_lstnew(str);
	if (!list->token->cmd)
		lst->type = CMD;
	else
		lst->type = ARG;
	ft_lstadd_back(&(list->token->cmd), lst);
	return (0);
}
