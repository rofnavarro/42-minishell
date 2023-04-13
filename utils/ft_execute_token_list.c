/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_token_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:36:09 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/13 04:29:53 by rinacio          ###   ########.fr       */
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

int	ft_is_executable(t_token *token)
{
	if (token->type == LESS || token->type == LESS_LESS)
		return (0);
	else if (token->prev && (token->prev->type == GREATER
			|| token->prev->type == GREATER_GREATER))
		return (0);
	return (1);
}

void	ft_token_type_exec(t_token *token)
{
	if (token->type == LESS)
		ft_get_input_file(token);
	else if (token->type == LESS_LESS)
		printf("heredoc \n");
	else if (token->type == GREATER || token->type == GREATER_GREATER)
		ft_open_output_file(token);
	else if (token->type == PIPE)
		ft_open_pipe();
	if (token->cmd[0] == NULL)
		return ;
}

	// printf("\n------------- Token list -------------\n");
	// ft_print_token_list();
	// printf("\n--------------------------------------\n\n");
void	ft_execute(t_token *token)
{
	char	*cmd_path;
	int		pid;

	ft_token_type_exec(token);
	if (ft_is_executable(token) && !is_builtin(token->cmd)
		&& ft_strncmp(token->cmd[0], "exit", 4) != 0)
	{
		cmd_path = ft_get_cmd_path(token);
		if (cmd_path)
		{
			pid = fork();
			if (pid < 0)
			{
				perror(NULL);
				return (ft_error(1, ""));
			}
			if (pid == 0)
				ft_child_process(token, cmd_path);
			ft_parent_process(pid);
			free(cmd_path);
		}
	}
	ft_close_pipes(token);
	ft_check_std_in_out(token);
}
