/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/27 16:45:03 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_token_list(void)
{
	t_token	*aux;
	int		wstatus;
	int		i = 0;

	g_data.count_pipes = 0;
	g_data.count_fork = 0;
	g_data.pid = malloc(sizeof(int) * g_data.token_list_size);
	g_data.fd = malloc(sizeof (int*) * (g_data.token_list_size - 1));
	while (i < g_data.token_list_size - 1)
		g_data.fd[i++] = malloc(sizeof(int) * 2);
	if (ft_check_sintax())
		return ft_exit();
	if (!g_data.token_start)
		return ;
	aux = g_data.token_start;
	while (aux && !g_data.aux_sig)
	{
		ft_execute(aux);
		aux = aux->next;
	}
	if (g_data.count_fork)
	{		
		int pid_waited;
		for(int i = 0; i < g_data.count_fork; i++)
		{
			wstatus = 0;
			pid_waited = waitpid(-1, &wstatus, 0);
			//printf("pid waited: %d", pid_waited);
			if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
			  	wstatus = WEXITSTATUS(wstatus);
			if (pid_waited == g_data.pid[g_data.count_fork - 1])
				g_data.exit_code = wstatus;
			if(WIFSIGNALED(wstatus))
			{
				g_data.exit_code = wstatus;
				if(g_data.exit_code == 131)
					printf("Quit (core dumped)\n");
				if(g_data.exit_code == 2)
				{
					g_data.exit_code = 130;
					printf("\n");
				}
			}
		}
	}
	free(g_data.pid);
	ft_free_matrix_int(g_data.fd, g_data.token_list_size - 1);
}

int	ft_is_executable(t_token *token)
{
	if (token->type == LESS || token->type == LESS_LESS || token->type == 8)
		return (0);
	else if (token->prev && (token->prev->type == GREATER
			|| token->prev->type == GREATER_GREATER
			|| token->prev->type == 8))
				return (0);
	return (1);
}

void	ft_heredoc(t_token *token)
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
		if(!g_data.input_hd)
		{
			printf("warning: here-document delimited by end-of-file (wanted `%s')\n", g_data.hd_delim);
			close(g_data.heredoc[1]);
			ft_heredoc_close_exit();
			exit(278);
			//break ;
		}
		else if (ft_strncmp(g_data.input_hd, g_data.hd_delim, ft_strlen(g_data.hd_delim)))
		{
			write(g_data.heredoc[1], g_data.input_hd, ft_strlen(g_data.input_hd));
			free(g_data.input_hd);
			write(g_data.heredoc[1], "\n", 1);
			g_data.input_hd = ft_strdup("");
		}
		else
		{
			free(g_data.input_hd);
			break ;
		}
	}
	close(g_data.heredoc[1]);
	ft_heredoc_close_exit();
	exit(0);
}

int	ft_token_type_exec(t_token *token)
{
	int pid;
	int wstatus;

	pid = -1;
	wstatus = 0;
	if ((token->type == GREATER || token->type == GREATER_GREATER) && token->cmd[0] == NULL)
		return (1);
	if (token->type == LESS)
		ft_get_input_file(token);
	else if (token->type == LESS_LESS)
	{
		if (pipe(g_data.heredoc) == -1)
		{
			perror(NULL);
			ft_error(1, "");
			return 0;
		}
		signal(SIGQUIT, SIG_IGN);
		g_data.sa_parent_heredoc.sa_handler = &handle_sig_parent_heredoc;
		sigaction(SIGINT, &g_data.sa_parent_heredoc, NULL);
		pid = fork();
		if (pid == 0)
		{
			//g_data.sa_child_heredoc.sa_handler = &handle_sig_child_heredoc;
			//sigaction(SIGINT, &g_data.sa_child_heredoc, NULL);
			ft_heredoc(token);
		}
		else
		{
			close(g_data.heredoc[1]);
			waitpid(pid, &wstatus, 0);
			if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
			{
			  	wstatus = WEXITSTATUS(wstatus);
				printf("wstatus: %d\n", wstatus);
			}
			//if(!WIFSIGNALED(wstatus))
			if (!g_data.aux_sig)
			{
				dup2(g_data.heredoc[0], STDIN_FILENO);
				close(g_data.heredoc[0]);
				token->type = 7;
				ft_execute(token);
				printf("heredoc não sinalizado\n");	
			}
			else
			{
				printf("heredoc sinalizado\n");
				g_data.aux_sig = 0;
				close(g_data.heredoc[0]);
			}
			token->type = 8;
		}
	}
	else if (token->type == GREATER || token->type == GREATER_GREATER)
		ft_open_output_file(token);
	else if (token->type == PIPE)
		ft_open_pipe();
	if (token->cmd[0] == NULL)
		return (0);
	return (0);
}

int	ft_check_slash(char *str)
{
	char	**str_split;
	int		result;

	str_split = ft_split(str, '/');
	if (str_split[1])
		result = 1;
	else
		result = 0;
	ft_free_matrix(str_split);
	return (result);
}

void	ft_execute(t_token *token)
{
	char	*cmd_path;

	cmd_path = NULL;
	if(!token->cmd[0] && token->type == 6)
		return ;
	if (ft_token_type_exec(token))
		return ;
	//printf("%s type %d is executable: %d\n", token->cmd[0], token->type, ft_is_executable(token));
	if (ft_is_executable(token) && !is_builtin(token->cmd)
		&& (ft_strncmp(token->cmd[0], "exit", 4) != 0 || ft_strlen(token->cmd[0]) != 4))
	{
		if (!ft_check_slash(token->cmd[0]))
			cmd_path = ft_get_cmd_path(token);
		if (ft_check_slash(token->cmd[0]) || cmd_path)
		{
			{
				signal(SIGINT, SIG_IGN);
				g_data.pid[g_data.count_fork] = fork();
				//printf("pid created: %d\n", g_data.pid[g_data.count_fork]);
				g_data.count_fork++;
				if (g_data.pid[g_data.count_fork - 1] < 0)
				{
					perror(NULL);
					return (ft_error(1, ""));
				}
				if (!g_data.pid[g_data.count_fork - 1])
				{
					if (cmd_path)
						ft_child_process(token, cmd_path);
					else
						ft_child_process(token, NULL);
				}
				if (cmd_path)
					free(cmd_path);
			}
		}
	}
	if(token->type == 7)
	 	dup2(g_data.stdin_copy, STDIN_FILENO);
	ft_close_pipes(token);
	ft_check_std_in_out(token);
	printf("passou aqui\n");
}
