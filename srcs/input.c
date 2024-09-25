/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:59:57 by rdiary            #+#    #+#             */
/*   Updated: 2024/09/25 17:44:40 by enarindr         ###   ########.fr       */
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
		// list->token->name[i];
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
	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[i])
	{
		while (str[i] && ft_iswite_space(str[i]))
			i++;
		if (str[i] && !ft_iswite_space(str[i]) && i != 0)
			new[j++] = ' ';
		while (str[i] && !ft_iswite_space(str[i]))
			new[j++] = str[i++];
	}
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
void	ft_add_heredoc(t_data *data, char *heredoc)
{
	char	*line;
	char	*read;

	line = NULL;
	while (1)
	{
		read = readline("> ");
		if (!read)
			return ;
		if (ft_strncmp(read, heredoc, ft_strlen(read)) == 0)
		{
			free (read);
			break;
		}
		line = ft_strjoin_2(line, read);
		line = ft_strjoin_2(line, ft_strdup("\n"));
	}
	ft_lstadd_back(&(data->list->token->heredoc), ft_lstnew(line));
}

void		ft_heredoc(t_data *data)
{
	int		i;
	int		j;
	char	*heredoc;

	i = 0;
	while ((data->input)[i + 1])
	{
		if (data->input[i] == '<' && data->input[i + 1] == '<')
		{
			heredoc = ft_calloc(sizeof(char), ft_strlen(data->input));
			if (!heredoc)
				return ;
			i += 2;
			j = 0;
			while ((data->input)[i] && !ft_iswite_space(data->input[i]))
				heredoc[j++] = data->input[i++];
			ft_add_heredoc(data, heredoc);
			free (heredoc);
		}
		i++;
	}
}

int	ft_end_pip(char *str)
{
	if (str[ft_strlen(str) - 1] == '|')
		return (1);
	return (0);
}

int	get_input(t_data *data)
{
	char	*rd_line;

	rd_line = readline("😂😂😂😂$ ");
	if (!rd_line)
		ft_exit(data);
	data->input = ft_epure_line(rd_line);
	free (rd_line);
	if (ft_strncmp(data->input, "exit", 4) == 0)
		ft_exit (data);
	if (ft_is_heredoc(data->input))
	{
		ft_heredoc(data);
	}
	if (data->list->token->heredoc)
	{
		while (data->list->token->heredoc)
		{
			printf ("%s", data->list->token->heredoc->content);
			data->list->token->heredoc = data->list->token->heredoc->next;
		}
	}
	// while (ft_end_pip(data->input))
	// {
	// 	rd_line = readline(">");
	// 	data->input = ft_strjoin_2(data->input, ft_epure_line(rd_line));
	// 	ft_heredoc(data);
	// }
	// if (data->input)
	// {
	// 	add_history(data->input);
	// 	parse_input(data);
	// }
	return (0);
}
