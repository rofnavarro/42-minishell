/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/11 23:34:42 by rinacio          ###   ########.fr       */
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
		return ;
	}
	aux = ft_find_aux();
	if (!aux)
		return (ft_free_restore_std());
	g_data.end_loop = 0;
	while (aux && !g_data.aux_sig)
	{
		ft_execute(aux);
		aux = aux->next;
	}
	if (!g_data.end_loop)
		ft_wait_children();
	ft_free_pid_fd();
}

int	handle_redirections(t_token *token)
{
	t_token	*aux;
	int		code;

	aux = token;
	while (aux)
	{
		if (aux->type == LESS)
		{
			code = handle_input(token, aux);
			if (code)
				return (code);
		}
		else if (aux->type == LESS_LESS)
			ft_execute_heredoc(aux);
		else if (aux->type == GREATER || aux->type == GREATER_GREATER)
		{
			code = handle_output(token, aux);
			if (code)
				return (code);
		}
		else if (aux->type == PIPE)
			break ;
		aux = aux->next;
	}
	return (0);
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
	if (token->prev && token->prev->type == PIPE)
	{
		if (ft_prev_pipe(token))
			return (1);
	}
	if (token->type != PIPE && token->type != GREATER && \
		token->type != GREATER_GREATER && ft_next_pipe(token))
		ft_open_pipe();
	if ((token->type == GREATER || token->type == GREATER_GREATER)
		&& token->cmd[0] == NULL)
		return (ft_greater(token));
	if (token->type == LESS)
		return (ft_less(token));
	else if ((token->type == PIPE && \
		(!token->prev || token->prev->type != LESS)))
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
	if ((!token->cmd[0] && (token->type == 6 || token->type == 8))
		|| ft_token_type_exec(token))
		return (ft_close_check_std(token));
	if (ft_is_executable(token) && !ft_echo_n(token) && (!is_builtin(token->cmd)
			|| ft_is_export_wo_arg(token)))
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
		if (cmd_path || ft_is_export_wo_arg(token))
			ft_fork(cmd_path, token);
	}
	ft_close_check_std(token);
}
