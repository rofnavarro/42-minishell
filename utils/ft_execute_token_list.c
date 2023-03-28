/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/03/28 15:03:33 by rinacio          ###   ########.fr       */
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
	ft_pwd(g_data->cmd, g_data);
	ft_get_cmd_path(g_data, token);
    printf("Executar token\n");
}

char	*ft_test_path(int i, t_program *g_data, t_token *token)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(g_data->path[i], "/");
	path = ft_strjoin(temp, token->cmd);
	if (access(path, F_OK) == 0)
	{
		free(temp);
		free(path);
		return(ft_strdup(path));
	}
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
		printf("%s: command not found\n", token->cmd);
		ft_error("", 127);
		// data->files_fd[0] = open("/dev/null", O_RDONLY);
	}
	return (cmd_path);
}