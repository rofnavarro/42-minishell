/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:17:06 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/13 04:22:47 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_process(t_token *token, char *cmd_path)
{
	if (token->prev && token->prev->type == LESS)
	{
		dup2(g_data.infile, STDIN_FILENO);
		close(g_data.infile);
	}
	if (token->type == PIPE)
		redirect_to_pipe();
	if (token->prev && token->prev->type == PIPE)
		redirect_from_pipe(token->type);
	if (execve(cmd_path, token->cmd, g_data.env) == -1)
	{
		perror(NULL);
		ft_error(1, "execve falhou\n");
		return ;
	}	
}

void	ft_parent_process(int pid)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
			wstatus = WEXITSTATUS(wstatus);
	g_data.exit_code = wstatus;
}
