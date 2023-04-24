/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/24 15:49:35 by rinacio          ###   ########.fr       */
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
	{
		g_data.fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	if (ft_check_sintax())
		return ft_exit();
	if (!g_data.token_start)
		return ;
	aux = g_data.token_start;
	while (aux)
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
			if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus))
			 	wstatus = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
			{
				wstatus = g_data.exit_code;
				//g_data.aux_sig = 0;
				g_data.exit_code = wstatus;
			}
			else if (pid_waited == g_data.pid[g_data.count_fork - 1])
			{
				g_data.exit_code = wstatus;
			}
			//printf("wstatus: %d\n", wstatus);
			//g_data.exit_code = wstatus;
		}
	}
	free(g_data.pid);
	ft_free_matrix_int(g_data.fd, g_data.token_list_size - 1);
}

int	ft_is_executable(t_token *token)
{
	if (token->type == LESS || token->type == LESS_LESS)
		return (0);
	else if (token->prev && (token->prev->type == GREATER
			|| token->prev->type == GREATER_GREATER
			|| token->prev->type == LESS_LESS))
				return (0);
	return (1);
}

void	ft_heredoc(t_token *token)
{
	char	*input;
	char	*aux;
	char	*next_line;

	input = ft_strdup("");
	next_line = ft_strdup("");
	while (ft_strncmp(next_line, token->next->cmd[0], ft_strlen(token->cmd[0])))
	{
		aux = ft_strdup(input);
		free(next_line);
		next_line = readline("> ");
		if (ft_strncmp(next_line, token->next->cmd[0],
				ft_strlen(token->cmd[0])))
		{
			free(input);
			input = ft_strjoin(aux, next_line);
			free(aux);
			aux = ft_strdup(input);
			free(input);
			input = ft_strjoin(aux, "\n");
			free(aux);
		}
		else
			free(aux);
	}
	free(next_line);
	if (!ft_strncmp(token->cmd[0], "cat", ft_strlen(token->cmd[0])))
		printf("%s", input);
	free(input);
}

int	ft_token_type_exec(t_token *token)
{
	if ((token->type == GREATER || token->type == GREATER_GREATER) && token->cmd[0] == NULL)
		return (1);
	if (token->type == LESS)
		ft_get_input_file(token);
	else if (token->type == LESS_LESS)
		ft_heredoc(token);
	else if (token->type == GREATER || token->type == GREATER_GREATER)
		ft_open_output_file(token);
	else if (token->type == PIPE)
		ft_open_pipe();
	if (token->cmd[0] == NULL)
		return (0);
	return (0);
}
	// printf("\n------------- Token list -------------\n");
	// ft_print_token_list();
	// printf("\n--------------------------------------\n\n");	

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
	if (ft_is_executable(token) && !is_builtin(token->cmd)
		&& (ft_strncmp(token->cmd[0], "exit", 4) != 0 || ft_strlen(token->cmd[0]) != 4))
	{
		if (!ft_check_slash(token->cmd[0]))
			cmd_path = ft_get_cmd_path(token);
		if (ft_check_slash(token->cmd[0]) || cmd_path)
		{
			{
				g_data.sa_child.sa_handler = &handle_sig_child;
				sigaction(SIGINT, &g_data.sa_child, NULL);
				sigaction(SIGQUIT, &g_data.sa_child, NULL);
				g_data.pid[g_data.count_fork] = fork();
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
	ft_close_pipes(token);
	ft_check_std_in_out(token);
}
