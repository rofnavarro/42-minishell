/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/05 12:22:43 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(void)
{
	while (g_data.stop == 0)
	{
		g_data.cmd = readline("hell$: ");
		if (!g_data.cmd) // verificar ctr+d (EOF - free all - exit)
			break ;
		while (ft_check_quotes(g_data.cmd))
			g_data.cmd = ft_strjoin_free(g_data.cmd, readline("> "));
		add_history(g_data.cmd);
		g_data.cmd = ft_switch_inside_quotation(g_data.cmd);
		g_data.cmd_token = ft_strtrim(ft_strtok(g_data.cmd, "|<<>>;")," ");
		while (g_data.cmd_token != NULL)
		{
			g_data.cmd_token = ft_switch_inside_quotation(g_data.cmd_token);
			ft_add_token(g_data.cmd_token, g_data.cmd_type);
			free(g_data.cmd_token);
			g_data.cmd_token = ft_strtrim(ft_strtok(NULL, "|<<>>;"), " ");
		}
		// ft_print_token_list();
		ft_execute_token_list();
		ft_free_token_list(g_data.token_start, 1);
		ft_exit();
		free(g_data.cmd);
	}
	rl_clear_history();
}
