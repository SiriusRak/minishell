/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/23 17:19:30 by enarindr         ###   ########.fr       */
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
void	ft_check_type(t_d_list *list, char *type)
{
	
}

int		ft_quotes(t_d_list *list, int start)
{
	int		len;
	int		i;
	int		j;
	char	*type;

	i = start + 1;
	j = 0;
	while (list->token->name[i] != '\'' && list->token->name[i] != '\"')
	{
		list->token->name[i];
		i++;
	}
	len = i - start + 1;
	type = malloc(sizeof (char) * len + 1);
	if (!len)
		return 0;
	
	while (start <= i)
	{
		type[j] = list->token->name[start + j];
		j++;
	}
	type[j] = '\0';
	ft_check_type(list, type);
	return (len);
}

void	ft_parse(t_d_list *list, t_data *data)
{
	int	i;

	i = 0;
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

int		ft_iswite_space(char c)
{
	if (c >= 9 && c <= 13 || c == ' ')
		return (1);
	return (0);
}

char	*ft_epure_line(char *str)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = 0;
	while (str[i])
	{
		while (ft_iswite_space(str[i]))
			i++;
		if (!t_iswite_space(str[i]) && i != 0)
			new[j++] = ' ';
		while (!t_iswite_space(str[i]))
			new[j++] = str[i++];		
	}
	free (str);
	return (new);
}

int		ft_is_heredoc(char	*str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

void	ft_heredoc(t_data *data)
{
	char	*prev;
	char	*next;
}

void	get_input(t_data *data)
{
	char	*rd_line;

	rd_line = readline("Minishell By Nary & Zazou $");
	data->input = ft_epure_line(rd_line);
	while (ft_is_heredoc(data->input))
		ft_heredoc(data->input);
	ft_herdoc(data);
	while (ft_end_pip(rd_line))
	{
		rd_line = ft_strjoin(rd_line, ft_epure_line(readline(">")));
		ft_heredoc(data);
	}

	// if (data->input)
	// {
	// 	add_history(data->input);
	// 	parse_input(data);
	// }
}

