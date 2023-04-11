/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/11 22:26:26 by rinacio          ###   ########.fr       */
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

void	ft_execute(t_token *token)
{
	char	*cmd_path;
	int		pid;
	int		wstatus;
	int		file;

	if (token->type == 1)
	{
		file = open(token->cmd[0], O_RDONLY);
		if(file == -1)
		{
			if (access(token->cmd[0], F_OK) == 0)
				return(ft_error(1, "open falhou\n"));
			file = open("/dev/null", O_RDONLY);
			perror(NULL);
			ft_error(1, "open falhou\n");
			return ;
		}
		dup2(file, STDIN_FILENO);
		close(file);
	}
	else if (token->type == 2)
	{
		printf("heredoc \n");
	}
	else if (token->type == 3 || token->type == 4)
	{
		if (token->type == 3)
			file = open(token->cmd[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else
			file = open(token->cmd[0], O_CREAT | O_WRONLY | O_APPEND, 0777);
		if(file == -1)
		{
			perror(NULL);
			ft_error(1, "open falhou\n");
			return ;
		}
		dup2(file, STDOUT_FILENO);
		close(file);
	}
	if (!token->prev || (token->prev->type!= 3 && token->prev->type!= 4))
	{
		if (token->type == 0)
		{
			if (pipe(g_data.fd[g_data.count_pipes % 2]) == -1)
			{
				perror(NULL);
				ft_error(1, "pipe falhou\n");
				return ;
			}
			g_data.count_pipes++;
		}
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
			if (token->type == 0)
			{
				close(g_data.fd[1 - g_data.count_pipes % 2][1]);
				if (token->prev && token->prev->type == 0)
					close(g_data.fd[g_data.count_pipes % 2][0]);
			}
			else if (token->prev && token->prev->type == 0)
				close(g_data.fd[1 - g_data.count_pipes % 2][0]);;
		}
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
