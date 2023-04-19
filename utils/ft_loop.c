/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/19 18:55:22 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(void)
{	
	char	*rl_text;

	while (g_data.stop == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		g_data.sa.sa_handler = &handle_sigint_empty;
		sigaction(SIGINT, &g_data.sa, NULL);
		g_data.user = find_var_value(g_data.env, "USER");
		rl_text = ft_strjoin(g_data.user, ":$ ");
		g_data.cmd = readline(rl_text);
		free(rl_text);
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
		// ft_print_token_list();
		ft_execute_token_list();
		ft_exit();
		ft_free_loop();
	}
}
