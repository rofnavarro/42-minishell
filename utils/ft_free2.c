/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:58:11 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/28 21:01:36 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc_close_exit(void)
{
	free(g_data.hd_delim);
	close(g_data.stdin_copy);
	close(g_data.stdout_copy);
	ft_free_loop();
	ft_free_data();
	rl_clear_history();
	free(g_data.pid);
	ft_free_matrix_int(g_data.fd, g_data.token_list_size - 1);
}

void	ft_free_child_process(void)
{
	ft_free_pid_fd();
	ft_free_loop();
	rl_clear_history();
	ft_free_data();
	ft_close_fds();
}

void	ft_close_check_std(t_token *token)
{
	ft_close_pipes(token);
	ft_check_std_in_out(token);
}
