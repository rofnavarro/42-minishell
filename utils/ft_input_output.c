/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:14:15 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/01 16:12:56 by rinacio          ###   ########.fr       */
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
		return (perror(NULL));
	dup2(g_data.outfile, STDOUT_FILENO);
	close(g_data.outfile);
}

char	**ft_new_cmd(t_token *token)
{
	int		i;
	char	**new_cmd;

	free(token->cmd);
	token->cmd = (char **)malloc(sizeof(char *) * 2);
	token->cmd[0] = ft_strdup(token->next->cmd[0]);
	token->cmd[1] = NULL;
	i = 0;
	while (token->next->cmd[i])
		i++;
	new_cmd = (char **)malloc((i + 1) * sizeof(char *));
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
	return (new_cmd);
}

void	ft_get_input_file(t_token *token)
{
	token->next->cmd = ft_new_cmd(token);
	token->type = 9;
	//ft_open_input_file(token);
	//ft_redirect_infile();
}

void	ft_open_input_file(t_token *token)
{
	g_data.infile = open(token->cmd[0], O_RDONLY);
	if (g_data.infile == -1)
	{
		if (access(token->cmd[0], F_OK) == 0)
		{
			g_data.infile = open("/dev/null", O_RDONLY);
			return (perror(token->cmd[0]));
		}
		g_data.infile = open("/dev/null", O_RDONLY);
		return (perror(token->cmd[0]));
	}
}

void	ft_redirect_infile(void)
{
	dup2(g_data.infile, STDIN_FILENO);
	close(g_data.infile);
}

void	ft_check_std_in_out(t_token *token)
{
	if (token->type == SEMICOLON || token->type == EOC)
	{
		if (ttyname(STDIN_FILENO) != ttyname(g_data.stdin_copy))
			dup2(g_data.stdin_copy, STDIN_FILENO);
		if (ttyname(STDOUT_FILENO) != ttyname(g_data.stdout_copy))
			dup2(g_data.stdin_copy, STDOUT_FILENO);
	}
}
