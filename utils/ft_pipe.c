/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:12:41 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/28 17:15:33 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_to_pipe(void)
{
	close(g_data.fd[g_data.count_pipes - 1][0]);
	dup2(g_data.fd[g_data.count_pipes - 1][1], STDOUT_FILENO);
	close(g_data.fd[g_data.count_pipes - 1][1]);
}

void	redirect_from_pipe(int type)
{
	int	i;

	if (type == PIPE)
		i = g_data.count_pipes - 2;
	else
		i = g_data.count_pipes - 1;
	dup2(g_data.fd[i][0], STDIN_FILENO);
	close(g_data.fd[i][0]);
}

void	ft_open_pipe(void)
{
	if (pipe(g_data.fd[g_data.count_pipes]) == -1)
		return (ft_error_perror(1, ""));
	g_data.count_pipes++;
}

void	ft_close_pipes(t_token *token)
{
	if (token->type == PIPE)
	{
		close(g_data.fd[g_data.count_pipes - 1][1]);
		if (token->prev && token->prev->type == PIPE)
			close(g_data.fd[g_data.count_pipes - 2][0]);
	}
	else if (token->prev && token->prev->type == PIPE)
		close(g_data.fd[g_data.count_pipes - 1][0]);
}
