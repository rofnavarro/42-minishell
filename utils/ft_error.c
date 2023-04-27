/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/27 15:19:56 by rinacio          ###   ########.fr       */
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
		close(g_data.stdin_copy);
		close(g_data.stdout_copy);
	}
}
