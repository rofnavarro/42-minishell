/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/27 17:47:04 by rferrero         ###   ########.fr       */
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
	if (ft_strncmp(g_data.cmd, "exit", 4) == 0)
	{
		g_data.stop = 1;
		ft_close_fds();
	}
}

void	ft_close_fds(void)
{
	close(g_data.stdin_copy);
	close(g_data.stdout_copy);
	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	printf("\n\nfechou tudo\n\n");
}
