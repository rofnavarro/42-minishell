/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:17:06 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/27 17:47:22 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_process(t_token *token, char *cmd_path)
{
	g_data.sa_child.sa_handler = &handle_sig_child;
	sigaction(SIGINT, &g_data.sa_child, NULL);
	sigaction(SIGQUIT, &g_data.sa_child, NULL);
	if (token->prev && token->prev->type == LESS)
	{
		dup2(g_data.infile, STDIN_FILENO);
		close(g_data.infile);
	}
	if (token->type == PIPE)
		redirect_to_pipe();
	if (token->prev && token->prev->type == PIPE)
		redirect_from_pipe(token->type);
	if (ft_is_builtin_child(token->cmd[0]) == TRUE)
		ft_exec_child_builtin(token, cmd_path);
	else if (cmd_path)
	{
		if (execve(cmd_path, token->cmd, g_data.env) == -1)
		{
			perror(NULL);
			ft_error(1, "");
			return ;
		}
	}
	if (!cmd_path)
	{
		if (execve(token->cmd[0], token->cmd, g_data.env) == -1)
		{
			perror(NULL);
			ft_error(1, "");
			return ;
		}		
	}
}

void	ft_exec_child_builtin(t_token *token, char *cmd_path)
{
	if (ft_strncmp(token->cmd[0], "env",
			ft_strlen(token->cmd[0])) == 0 && token->cmd[1] == NULL)
		ft_print_env(token->cmd[0]);
	else if (ft_strncmp(token->cmd[0], "pwd", ft_strlen(token->cmd[0])) == 0 && \
				token->cmd[1] == NULL)
		ft_pwd(token->cmd[0]);
	else if (ft_strncmp(token->cmd[0], "echo", ft_strlen(token->cmd[0])) == 0)
		ft_echo(token->cmd);
	free(cmd_path);
	ft_free_child_process();
	exit (0);
}

void	ft_free_child_process(void)
{
	ft_free_loop();
	rl_clear_history();
	ft_free_data();
	ft_close_fds();
}
