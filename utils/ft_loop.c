/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/28 20:37:29 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(void)
{	
	while (g_data.stop == 0)
	{
		ft_loop_start();
		if (!g_data.cmd)
			break ;
		while (ft_check_quotes(g_data.cmd))
			g_data.cmd = ft_strjoin_free(g_data.cmd, readline("> "));
		add_history(g_data.cmd);
		g_data.cmd = ft_switch_inside_quotation(g_data.cmd);
		g_data.cmd_token = ft_strtrim(ft_strtok(g_data.cmd, "|<<>>;"), " ");
		while (g_data.cmd_token != NULL)
		{
			ft_add_token(g_data.cmd_token, g_data.cmd_type);
			free(g_data.cmd_token);
			g_data.cmd_token = ft_strtrim(ft_strtok(NULL, "|<<>>;"), " ");
		}
		ft_quotes_handler();
		ft_print_token_list();
		if (!g_data.token_start)
			continue ;
		ft_execute_token_list();
		ft_free_loop();
	}
}

void	ft_loop_start(void)
{
	ft_signal_setup();
	g_data.token_list_size = 0;
	g_data.user = find_var_value(g_data.env, "USER");
	g_data.rl_text = ft_strjoin(g_data.user, ":$ ");
	g_data.cmd = readline(g_data.rl_text);
	free(g_data.rl_text);
}
