/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/03/28 15:40:54 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute_token_list(t_program *g_data)
{
	t_token	*aux;

	if (!g_data->token_start)
		return ;
	aux = g_data->token_start;
	while (aux)
	{
		ft_execute(g_data, aux);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		aux = aux->next;
	}
}

void    ft_execute(t_program *g_data, t_token *token)
{
	char	*cmd_path;
	int		pid1;

	ft_pwd(g_data->cmd, g_data);
	cmd_path = ft_get_cmd_path(g_data, token);
	pid1 = fork();
	if (pid1 < 0)
		ft_error("Error while forking.\n", 1);
	if (pid1 == 0)
	{
		if (execve(cmd_path, token->cmd, g_data->env) == -1)
			ft_error("Failed executing command", errno);
	}
}

char	*ft_test_path(int i, t_program *g_data, t_token *token)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(g_data->path[i], "/");
	path = ft_strjoin(temp, token->cmd[0]);
	if (access(path, F_OK) == 0)
	{
		free(temp);
		free(path);
		return(ft_strdup(path));
	}	char	*cmd_path;
	free(temp);
	free(path);
	return (NULL);
}

char	*ft_get_cmd_path(t_program *g_data, t_token *token)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (g_data->path[i])
	{
		cmd_path = ft_test_path(i, g_data, token);
		if (cmd_path)
			break ;
		i++;
	}
	if (cmd_path == NULL)
	{
		printf("%s: command not found\n", token->cmd[0]);
		ft_error("", 127);
	}
	return (cmd_path);
}
