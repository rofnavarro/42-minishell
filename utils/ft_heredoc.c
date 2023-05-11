/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:47:26 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/11 18:23:19 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_heredoc(t_token *token)
{
	int	pid;

	if (pipe(g_data.heredoc) == -1)
		return (ft_error_perror(1));
	signal(SIGQUIT, SIG_IGN);
	g_data.sa_parent_heredoc.sa_handler = &handle_sig_parent_heredoc;
	sigaction(SIGINT, &g_data.sa_parent_heredoc, NULL);
	pid = fork();
	if (pid < 0)
		return (ft_error_perror(1));
	if (pid == 0)
		ft_heredoc_child(token);
	else
		ft_heredoc_parent(pid, token);
}

void	ft_heredoc_parent(int pid, t_token *token)
{
	int	wstatus;

	wstatus = 0;
	close(g_data.heredoc[1]);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
		wstatus = WEXITSTATUS(wstatus);
	if (!g_data.aux_sig)
	{
		dup2(g_data.heredoc[0], STDIN_FILENO);
		close(g_data.heredoc[0]);
		token->type = 7;
	}
	else
	{
		g_data.aux_sig = 0;
		close(g_data.heredoc[0]);
	}
	token->type = 8;
}

void	ft_heredoc_child(t_token *token)
{
	g_data.sa_child_heredoc.sa_handler = &handle_sig_child_heredoc;
	sigaction(SIGINT, &g_data.sa_child_heredoc, NULL);
	close(g_data.heredoc[0]);
	g_data.hd_delim = ft_strdup(token->next->cmd[0]);
	g_data.input_hd = ft_strdup("");
	while (TRUE)
	{
		free(g_data.input_hd);
		g_data.input_hd = readline("> ");
		if (!g_data.input_hd)
			ft_heredoc_eof();
		else if (ft_strncmp(g_data.input_hd, g_data.hd_delim,
				ft_strlen(g_data.hd_delim)))
			ft_write_heredoc();
		else
			break ;
	}
	free(g_data.input_hd);
	close(g_data.heredoc[1]);
	ft_heredoc_close_exit();
	exit(0);
}

void	ft_write_heredoc(void)
{
	write(g_data.heredoc[1], g_data.input_hd, ft_strlen(g_data.input_hd));
	free(g_data.input_hd);
	write(g_data.heredoc[1], "\n", 1);
	g_data.input_hd = ft_strdup("");
}

void	ft_heredoc_eof(void)
{
	printf("warning: here-document delimited by end-of-file");
	printf(" (wanted `%s')\n", g_data.hd_delim);
	close(g_data.heredoc[1]);
	ft_heredoc_close_exit();
	exit(0);
}
