/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:17:53 by enarindr          #+#    #+#             */
/*   Updated: 2024/10/16 21:05:30 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_expand_key(char *str, int start)
{
	
}

char	*ft_expand(char *str)
{
	char	*prev;
	char	*next;
	char	*value;
	int		i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] != ' ')
		{
			value = ft_expand_key(str, i + 1);
			prev = ft_substr(str, 0, i + 1);
			next = ft_substr(str, i, ft_strlen(str) - i);
			i += ft_strlen(value);
			prev = ft_strjoin_2(prev, value);
			free (str);
			str = ft_strjoin_2(prev, next);
		}
		else
			i++;
	}
	return(str);	
}

char	*ft_clean_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
				c = '\'';
			else if (str[i] == '\"')
				c = '\"';
			ft_strlcpy(&(str[i]), &(str[i + 1]), ft_strlen(str) + 1);
			while (str[i] != c)
			{
				if (c == '\"' && str[i + 1])
				{
					if (str[i] == '$' && str[i + 1] != ' ')
						str = ft_expand(str);
				}
				i++;
			}
			ft_strlcpy(&(str[i]), &(str[i + 1]), ft_strlen(str) + 1);
		}
		i++;
	}
	return(str);
}

int	is_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		else if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

char	*ft_clear_word(char *str)
{
	if (is_quote(str))
	{
		// if (is_quote(str) == 2)
		// 	str = ft_expand(str);
		str = ft_clean_quote(str);
	}
	return (str);
}

int	ft_add_out(t_d_list *list, char *str, int i)
{
	t_list	*lst;

	if (!ft_check_error(str))
		return (1);
	str = ft_clear_word(str);
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
	str = ft_clear_word(str);
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
	str = ft_clear_word(str);
	lst = ft_lstnew(str);
	if (!list->token->cmd)
		lst->type = CMD;
	else
		lst->type = ARG;
	ft_lstadd_back(&(list->token->cmd), lst);
	return (0);
}
