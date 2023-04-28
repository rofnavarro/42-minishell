/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:42:00 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/28 17:43:07 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signals_exit_code(int wstatus)
{
	g_data.exit_code = wstatus;
	if (g_data.exit_code == 131)
		printf("Quit (core dumped)\n");
	if (g_data.exit_code == 2)
	{
		g_data.exit_code = 130;
		printf("\n");
	}
}

void	ft_signal_setup(void)
{
	signal(SIGQUIT, SIG_IGN);
	g_data.sa.sa_handler = &handle_sigint_empty;
	g_data.sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &g_data.sa, NULL);
}
