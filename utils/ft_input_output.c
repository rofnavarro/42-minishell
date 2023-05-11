/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:14:15 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/11 22:48:15 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_output_file(t_token *token)
{
	if (token->type == GREATER)
		g_data.outfile = open(token->next->cmd[0],
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		g_data.outfile = open(token->next->cmd[0],
				O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (g_data.outfile == -1)
	{
		g_data.outfile = open("/dev/null", O_WRONLY);
		perror(token->next->cmd[0]);
		return (1);
	}
	dup2(g_data.outfile, STDOUT_FILENO);
	close(g_data.outfile);
	return (0);
}

void	ft_get_input_file(t_token *token)
{
	token->next->cmd = ft_new_cmd(token);
	token->type = 9;
}

int	ft_open_input_file(t_token *token)
{
	g_data.infile = open(token->cmd[0], O_RDONLY);
	if (g_data.infile == -1)
	{
		if (access(token->cmd[0], F_OK) == 0)
		{
			g_data.infile = open("/dev/null", O_RDONLY);
			perror(token->cmd[0]);
			return (1);
		}
		g_data.infile = open("/dev/null", O_RDONLY);
		perror(token->cmd[0]);
		return (1);
	}
	return (0);
}

void	ft_redirect_infile(void)
{
	dup2(g_data.infile, STDIN_FILENO);
	close(g_data.infile);
}

void	ft_check_std_in_out(t_token *token)
{
	if (token->type == SEMICOLON || token->type == EOC)
	{
		if (ttyname(STDIN_FILENO) != ttyname(g_data.stdin_copy))
			dup2(g_data.stdin_copy, STDIN_FILENO);
		if (ttyname(STDOUT_FILENO) != ttyname(g_data.stdout_copy))
			dup2(g_data.stdin_copy, STDOUT_FILENO);
	}
	else if (token->prev && (token->prev->type == GREATER
			|| token->prev->type == GREATER_GREATER)
		&& (token->type == PIPE))
	{
		if (ttyname(STDOUT_FILENO) != ttyname(g_data.stdout_copy))
			dup2(g_data.stdin_copy, STDOUT_FILENO);
	}
}
