/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:14:15 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/18 17:55:19 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_open_output_file(t_token *token)
{
	if (token->type == GREATER)
		g_data.outfile = open(token->next->cmd[0],
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		g_data.outfile = open(token->next->cmd[0],
				O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (g_data.outfile == -1)
	{
		perror(NULL);
		ft_error(1, "open write falhou\n");
		return ;
	}
	if (token->next->type != EOC)
		dup2(g_data.outfile, STDOUT_FILENO);
	close(g_data.outfile);
}

void	ft_get_input_file(t_token *token)
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
	ft_open_input_file(token);
}

void	ft_open_input_file(t_token *token)
{
	g_data.infile = open(token->cmd[0], O_RDONLY);
	if (g_data.infile == -1)
	{
		if (access(token->cmd[0], F_OK) == 0)
		{
			perror(token->cmd[0]);
			return (ft_error(1, ""));
		}
		g_data.infile = open("/dev/null", O_RDONLY);
		perror(token->cmd[0]);
		ft_error(1, "");
		return ;
	}	
}

void	ft_check_std_in_out(t_token *token)
{
	if (token->type == SEMICOLON || token->type == EOC)
	{
		if (!isatty(STDIN_FILENO))
			dup2(g_data.stdin_copy, STDIN_FILENO);
		if (!isatty(STDOUT_FILENO))
			dup2(g_data.stdin_copy, STDOUT_FILENO);
	}
}
