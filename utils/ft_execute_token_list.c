/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/30 03:14:04 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_token_list(void)
{
	t_token	*aux;
	int		i;

	i = 0;
	ft_execute_start();
	while (i < g_data.token_list_size - 1)
		g_data.fd[i++] = malloc(sizeof(int) * 2);
	if (ft_check_sintax())
	{
		ft_free_pid_fd();
		return (ft_exit());
	}
	aux = g_data.token_start;
	while (aux && !g_data.aux_sig)
	{
		ft_execute(aux);
		aux = aux->next;
	}
	ft_wait_children();
	ft_free_pid_fd();
}

void	ft_execute_start(void)
{
	g_data.count_pipes = 0;
	g_data.count_fork = 0;
	g_data.pid = malloc(sizeof(int) * g_data.token_list_size);
	g_data.fd = malloc(sizeof(int *) * (g_data.token_list_size - 1));
	if (!g_data.pid || !g_data.fd)
	{
		ft_free_pid_fd();
		return (ft_exit());
	}
}

int	ft_token_type_exec(t_token *token)
{
	if ((token->type == GREATER || token->type == GREATER_GREATER)
		&& token->cmd[0] == NULL)
	{
		if (token->type == GREATER)
			g_data.outfile = open(token->next->cmd[0],
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else
			g_data.outfile = open(token->next->cmd[0],
					O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (g_data.outfile == -1)
			perror(NULL);
		return (1);
	}
	if (token->type == LESS)
		ft_get_input_file(token);
	else if (token->type == LESS_LESS)
		ft_execute_heredoc(token);
	else if (token->type == GREATER || token->type == GREATER_GREATER)
		ft_open_output_file(token);
	else if (token->type == PIPE)
		ft_open_pipe();
	if (token->cmd[0] == NULL && (token->type != GREATER
			|| token->type != GREATER_GREATER))
		return (0);
	return (0);
}

void	ft_execute(t_token *token)
{
	char	*cmd_path;

	cmd_path = NULL;
	if ((!token->cmd[0] && token->type == 6) || ft_token_type_exec(token))
		return ;
	if (ft_is_executable(token) && !ft_echo_n(token) && !is_builtin(token->cmd))
	{
		if (!ft_check_slash(token->cmd[0]))
			cmd_path = ft_get_cmd_path(token);
		else
		{
			if (access(token->cmd[0], X_OK) != 0)
			{
				perror(token->cmd[0]);
				g_data.exit_code = 127;
				return ;
			}
			ft_fork(cmd_path, token);
		}
		if (cmd_path)
			ft_fork(cmd_path, token);
	}
	ft_close_pipes(token);
	ft_check_std_in_out(token);
}
