/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/13 00:39:46 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_token_list(void)
{
	t_token	*aux;

	if (!g_data.token_start)
		return ;
	aux = g_data.token_start;
	while (aux)
	{
		ft_execute(aux);
		aux = aux->next;
	}
}

void	redirect_to_pipe(void)
{
	int i;

	i = 1 - g_data.count_pipes % 2;
	close(g_data.fd[i][0]);
	dup2(g_data.fd[i][1], STDOUT_FILENO);
	close(g_data.fd[i][1]);
}


void	redirect_from_pipe(int type)
{
	int	i;

	if (type == 0)
		i = g_data.count_pipes % 2;
	else
		i = 1 - g_data.count_pipes % 2;
	dup2(g_data.fd[i][0], STDIN_FILENO);
	close(g_data.fd[i][0]);
}

int ft_is_executable(t_token *token)
{
	if (token->type == 1 || token->type == 2)
		return 0;
	else if (token->prev && (token->prev->type == 3 || token->prev->type == 4))
		return 0;
	return 1;
}

void ft_aux(t_token *token)
{
	int		i;
	char	**new_cmd;

	token->cmd[0] = ft_strdup(token->next->cmd[0]);
	token->cmd[1] = NULL;
	i = 0;
	while (token->next->cmd[i])
		i++;
	new_cmd = (char **)malloc(i * sizeof(char *));
	i = 0;
	free(token->next->cmd[0]);
	while (token->next->cmd[i + 1])
	{
		new_cmd[i] = ft_strdup(token->next->cmd[i + 1]);
		free(token->next->cmd[i + 1]);
		i++;
	}
	new_cmd[i] = NULL;
	free(token->next->cmd[i + 1]);
	free(token->next->cmd);
	token->next->cmd = new_cmd;
}

void	ft_execute(t_token *token)
{
	char	*cmd_path;
	int		pid;
	int		wstatus;

	// printf("\n------------- Token list -------------\n");
	// ft_print_token_list();
	// printf("\n--------------------------------------\n\n");
	if (token->type == 1)
	{
		ft_aux(token);
		g_data.infile = open(token->cmd[0], O_RDONLY);
		if(g_data.infile == -1)
		{
			if (access(token->cmd[0], F_OK) == 0)
				return(ft_error(1, "open read falhou\n"));
			g_data.infile = open("/dev/null", O_RDONLY);
			perror(NULL);
			ft_error(1, "open read falhou\n");
			return ;
		}
	}
	else if (token->type == 2)
	{
		printf("heredoc \n");
	}
	else if (token->type == 3 || token->type == 4)
	{
		if (token->type == 3)
			g_data.outfile = open(token->next->cmd[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else
			g_data.outfile = open(token->next->cmd[0], O_CREAT | O_WRONLY | O_APPEND, 0777);
		if(g_data.outfile == -1)
		{
			perror(NULL);
			ft_error(1, "open write falhou\n");
			return ;
		}
		dup2(g_data.outfile, STDOUT_FILENO);
		close(g_data.outfile);
	}
	else if (token->type == 0)
	{
		if (pipe(g_data.fd[g_data.count_pipes % 2]) == -1)
		{
			perror(NULL);
			ft_error(1, "pipe falhou\n");
			return ;
		}
		g_data.count_pipes++;
	}
	if (ft_is_executable(token))
	{
		if (!is_builtin(token->cmd) && ft_strncmp(token->cmd[0], "exit", 4) != 0)
		{
			cmd_path = ft_get_cmd_path(token);
			if (cmd_path)
			{
				pid = fork();
				if (pid < 0)
				{
					perror(NULL);
					ft_error(1, "fork falhou\n");
					return ;
				}
				if (pid == 0)
				{
					if (token->prev && token->prev->type == 1)
					{
						dup2(g_data.infile, STDIN_FILENO);
						close(g_data.infile);
					}
					if (token->type == 0)
						redirect_to_pipe();
					if (token->prev && token->prev->type == 0)
						redirect_from_pipe(token->type);
					if (execve(cmd_path, token->cmd, g_data.env) == -1)
					{
						perror(NULL);
						ft_error(1, "execve falhou\n");
						return ;
					}
				}
				waitpid(pid, &wstatus, 0);
				if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
						wstatus = WEXITSTATUS(wstatus);
				g_data.exit_code = wstatus;
				free(cmd_path);
			}
		}
	}
	if (token->type == 0)
	{
		close(g_data.fd[1 - g_data.count_pipes % 2][1]);
		if (token->prev && token->prev->type == 0)
			close(g_data.fd[g_data.count_pipes % 2][0]);
	}
	else if (token->prev && token->prev->type == 0)
		close(g_data.fd[1 - g_data.count_pipes % 2][0]);
	if (token->type == 5 || token->type == 6)
	{
		if (!isatty(STDIN_FILENO))
			dup2(g_data.stdin_copy, STDIN_FILENO);
		if (!isatty(STDOUT_FILENO))
			dup2(g_data.stdin_copy, STDOUT_FILENO);
	}
}

char	*ft_test_path(int i, t_token *token)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(g_data.path[i], "/");
	path = ft_strjoin(temp, token->cmd[0]);
	free(temp);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*ft_get_cmd_path(t_token *token)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	get_path();
	if (g_data.path == NULL)
	{
		printf("command not found: %s\n", token->cmd[0]);
		return (NULL);
	}
	while (g_data.path[i])
	{
		cmd_path = ft_test_path(i, token);
		if (cmd_path)
			break ;
		i++;
	}
	if (cmd_path == NULL)
		ft_cmd_not_found(token->cmd[0]);
	return (cmd_path);
}

void	ft_cmd_not_found(char *cmd)
{
	if (ft_strncmp(cmd, "$?", 2) == 0 && \
		ft_strlen(cmd) == 2)
		printf("command not found: %d\n", g_data.exit_code);
	else
		printf("command not found: %s\n", cmd);
	g_data.exit_code = 127;
}
