/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 02:39:36 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/27 15:38:31 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_empty(int sig)
{
	if (sig == SIGINT)
	{
		g_data.exit_code = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sig_child(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	else if (sig == SIGINT)
		exit(130);
}

void	handle_sig_child_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		close(g_data.heredoc[1]);
		ft_heredoc_close_exit();
		exit(130);
	}
}

void	handle_sig_parent_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_data.aux_sig = 1;
		g_data.exit_code = 130;
		printf("\n");
	}
}