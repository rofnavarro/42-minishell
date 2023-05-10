/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/04 20:49:20 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_token_list(void)
{
	t_token	*aux;
	int		i;

	i = 0;
	ft_execute_start();
	if (ft_check_sintax())
	{
		ft_free_pid_fd();
		return ;
	}
	while (i < g_data.token_list_size - 1)
		g_data.fd[i++] = malloc(sizeof(int) * 2);
	if (handle_redirections(g_data.token_start) == 2)
	{
		aux = ft_next_pipe(g_data.token_start);
		if (!aux)
		{
			ft_free_pid_fd();
			dup2(g_data.stdin_copy, STDIN_FILENO);
			dup2(g_data.stdout_copy, STDOUT_FILENO);
			return ;
		}
		ft_open_pipe();
	}
	else
		aux = g_data.token_start;
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

	aux = token;
	while (aux)
	{
		if (aux->type == LESS)
		{
			if (aux->next->cmd[1])
				aux->cmd = ft_check_args_after_redirection(aux);
			if (ft_open_input_file(aux->next))
			{
				g_data.exit_code = 1;
				if (ft_strncmp("echo", token->cmd[0], 4) == 0 && ft_strlen(token->cmd[0]) == 4)
				{
					dup2(g_data.stdin_copy, STDIN_FILENO);
					return (2);
				}
				ft_redirect_infile();
				if (aux->next->type == PIPE)
					return (1);
				return (2);
			}
			ft_redirect_infile();
		}
		else if (aux->type == GREATER || aux->type == GREATER_GREATER)
		{
			if (aux->next->cmd[1])
				aux->cmd = ft_check_args_after_redirection(aux);
			if (ft_open_output_file(aux))
			{
				g_data.exit_code = 1;
				dup2(g_data.stdout_copy, STDOUT_FILENO);
				return (2);
			}
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
		g_data.end_loop = 0;
		if (handle_redirections(token) == 2)
		{
			g_data.end_loop = 1;
			return (1);
		}
	}
	if (token->type != PIPE && token->type != GREATER && token->type != GREATER_GREATER && ft_next_pipe(token))
		ft_open_pipe();
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
	{
		if (token->cmd[0])
			return (0);
		else
		{
			ft_get_input_file(token);
			return (1);
		}
	}
	else if (token->type == LESS_LESS)
		ft_execute_heredoc(token);
	else if ((token->type == PIPE && (!token->prev || token->prev->type != LESS)))
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
	{
		ft_close_pipes(token);
		ft_check_std_in_out(token);
		return ;
	}
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
	ft_close_pipes(token);
	//ft_check_std_in_out(token);
}
