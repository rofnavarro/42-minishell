/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:14:15 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/10 22:31:52 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input(t_token *token, t_token *aux)
{
	if (aux->next->cmd[1])
		aux->cmd = ft_check_args_after_redirection(aux);
	if (ft_open_input_file(aux->next))
	{
		g_data.exit_code = 1;
		if (token->cmd[0] && ft_strncmp("echo", token->cmd[0], 4) == 0
			&& ft_strlen(token->cmd[0]) == 4)
		{
			dup2(g_data.stdin_copy, STDIN_FILENO);
			return (2);
		}
		ft_redirect_infile();
		if (aux->next->type == PIPE)
			return (1);
		return (2);
	}
	ft_redirect_infile();
	return (0);
}

int	handle_output(t_token *token, t_token *aux)
{
	if (aux->next->cmd[1])
		aux->cmd = ft_check_args_after_redirection(aux);
	if (ft_open_output_file(aux))
	{
		g_data.exit_code = 1;
		dup2(g_data.stdout_copy, STDOUT_FILENO);
		return (2);
	}
	return (0);
}

void	ft_free_restore_std(void)
{
	ft_free_pid_fd();
	dup2(g_data.stdin_copy, STDIN_FILENO);
	dup2(g_data.stdout_copy, STDOUT_FILENO);
}

t_token	*ft_find_aux(void)
{
	t_token	*aux;

	if (handle_redirections(g_data.token_start) == 2)
	{
		aux = ft_next_pipe(g_data.token_start);
		if (!aux)
			return (NULL);
		ft_open_pipe();
	}
	else
		aux = g_data.token_start;
	return (aux);
}
