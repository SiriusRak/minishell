/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:57:26 by enarindr          #+#    #+#             */
/*   Updated: 2024/12/04 14:13:39 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipe_error(char *str, int i)
{
	i++;
	while (str[i] && ft_iswite_space(str[i]))
		i++;
	if (str[i] == '|')
		return (1);
	return (0);
}

int	ft_pars_error(t_list *list)
{
	t_list	*lst;

	lst = list;
	while (lst)
	{
		printf("%s\n", lst->content);
		if (lst->content && !ft_check_error(lst->content))
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	ft_all_error(t_d_list *list)
{
	printf("%s\n", list->token->cmd->content);
	if (list)
	{
		if (list->token)
		{
			if (list->token->cmd)
			{
				if (ft_pars_error(list->token->cmd))
					return (1);
			}
			if (list->token->in)
			{
				if (ft_pars_error(list->token->in))
					return (1);
			}
			if (list->token->out)
			{
				if (ft_pars_error(list->token->out))
					return (1);
			}
		}
	}
	return (0);
}

void	ft_export_error(char *str, int i, char c)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("export: ", 2);
	if (i == 0)
	{
		ft_putchar_fd('`', 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		ft_putchar_fd('-', 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
}
