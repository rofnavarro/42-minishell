/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:12:41 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/19 18:38:47 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_to_pipe(void)
{
	int	i;

	i = 1 - g_data.count_pipes % 2;
	close(g_data.fd[i][0]);
	dup2(g_data.fd[i][1], STDOUT_FILENO);
	close(g_data.fd[i][1]);
}

void	redirect_from_pipe(int type)
{
	int	i;

	if (type == PIPE)
		i = g_data.count_pipes % 2;
	else
		i = 1 - g_data.count_pipes % 2;
	dup2(g_data.fd[i][0], STDIN_FILENO);
	close(g_data.fd[i][0]);
}

void	ft_open_pipe(void)
{
	if (pipe(g_data.fd[g_data.count_pipes % 2]) == -1)
	{
		printf("pipe[%d][0] aberto\n", g_data.count_pipes % 2);
		printf("pipe[%d][1] aberto\n", g_data.count_pipes % 2);
		perror(NULL);
		ft_error(1, "");
		return ;
	}
	g_data.count_pipes++;
}

void	ft_close_pipes(t_token *token)
{
	if (token->type == PIPE)
	{
		{
			close(g_data.fd[1 - g_data.count_pipes % 2][1]);
			printf("pipe [%d][1] fechado\n processo %d\n", 1 - g_data.count_pipes % 2, getpid());
		}
		if (token->prev && token->prev->type == 0)
		{
			close(g_data.fd[g_data.count_pipes % 2][0]);
			printf("pipe [%d][0] fechado\n processo %d\n", 1 - g_data.count_pipes % 2, getpid());
		}
	}
	else if (token->prev && token->prev->type == 0)
	{
		close(g_data.fd[1 - g_data.count_pipes % 2][0]);
		printf("pipe [%d][0] fechado\n processo %d\n", 1 - g_data.count_pipes % 2, getpid());
	}
}
