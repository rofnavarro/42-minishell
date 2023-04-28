/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/28 20:23:53 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(int arg, char *msg)
{
	g_data.exit_code = arg;
	printf("%s\n", msg);
}

void	ft_exit(void)
{
	g_data.stop = 1;
	ft_close_fds();
}

void	ft_close_fds(void)
{
	close(g_data.stdin_copy);
	close(g_data.stdout_copy);
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

void	ft_error_perror(int arg, char *msg)
{
	perror(NULL);
	ft_error(arg, msg);
}

void	ft_free_pid_fd(void)
{
	free(g_data.pid);
	ft_free_matrix_int(g_data.fd, g_data.token_list_size - 1);
}
