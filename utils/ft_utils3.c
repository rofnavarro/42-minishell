/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:14:15 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/11 22:52:21 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_greater(t_token *token)
{
	if (token->type == GREATER)
		g_data.outfile = open(token->next->cmd[0],
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		g_data.outfile = open(token->next->cmd[0],
				O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (g_data.outfile == -1)
		perror(NULL);
	else
	{
		dup2(g_data.outfile, STDOUT_FILENO);
		close(g_data.outfile);
	}
	return (1);
}

int	ft_less(t_token *token)
{
	if (token->cmd[0])
		return (0);
	ft_get_input_file(token);
	return (1);
}

int	ft_prev_pipe(t_token *token)
{
	g_data.end_loop = 0;
	if (handle_redirections(token) == 2)
	{
		g_data.end_loop = 1;
		return (1);
	}
	return (0);
}
