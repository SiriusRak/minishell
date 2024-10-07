/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdiary <rdiary@student.42antananarivo      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:21:42 by rdiary            #+#    #+#             */
/*   Updated: 2024/10/07 16:48:35 by rdiary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_cmd(t_data *data)
{
	char	**env;
	char	**arg;
	pid_t	pid;

	pid = fork();
	env = ft_lst_to_char(data->env);
	arg = ft_lst_to_char(data->list->token->arg);
	if (pid == 0)
	{
		if (execve(data->list->token->path, arg, env) == -1)
			perror("execve");
		exit (1);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");
	ft_free_split(env);
	ft_free_split(arg);
}

int	ft_check_cmd(t_data *data)
{
	t_d_list	*head;
	char		*cmd;
	int			checker;

	head = data->list;
	checker = 0;
	while (head)
	{
		cmd = ft_strdup(head->token->cmd->content);
		head->token->path = ft_find_in_path(cmd);
		if (ft_is_builtin((char *)head->token->cmd->content))
			checker = 1;
		else if (head->token->path && checker == 0)
			checker = 1;
		else
		{
			perror("cmd");
			return (0);
		}
		head = head->next;
		free(cmd);
	}
	return (1);
}

void	ft_execute(t_data *data)
{
	char	*arg;
	int		is_cmd;

	if (data->list->token->out != NULL)
		ft_redir(data->list->token->out, data->list->token->out->type);
	arg = ft_strdup(data->list->token->arg->content);
	is_cmd = ft_check_cmd(data);
	if (ft_is_builtin((char *)data->list->token->cmd->content) && is_cmd)
		ft_execute_builtin(data, data->list->token->cmd->content, arg);
	else if (!ft_is_builtin((char *)data->list->token->cmd->content) && is_cmd)
		ft_execute_cmd(data);
	free(arg);
}
