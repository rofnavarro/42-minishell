/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/05 15:28:50 by rferrero         ###   ########.fr       */
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

void	ft_execute(t_token *token)
{
	char	*cmd_path;
	int		pid;
	int		wstatus;

	if (!is_builtin(token->cmd) && ft_strncmp(token->cmd[0], "exit", 4) != 0)
	{
		cmd_path = ft_get_cmd_path(token);
		if (cmd_path)
		{
			pid = fork();
			if (pid < 0)
			{
				ft_error(errno);
				return ;
			}
			if (pid == 0)
			{
				if (execve(cmd_path, token->cmd, g_data.env) == -1)
					return (ft_error(errno));
			}
			waitpid(pid, &wstatus, 0);
			if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
				wstatus = WEXITSTATUS(wstatus);
			g_data.exit_code = wstatus;
			free(cmd_path);
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
	{
		if (ft_strncmp(token->cmd[0], "$?", 2) == 0 && \
			ft_strlen(token->cmd[0]) == 2)
			printf("command not found: %d\n", g_data.exit_code);
		else
			printf("command not found: %s\n", token->cmd[0]);
		g_data.exit_code = 127;
	}
	return (cmd_path);
}
