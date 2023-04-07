/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/07 16:08:00 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(void)
{
	while (g_data.stop == 0)
	{
		char	*user;
	
		user = find_var_value(g_data.env, "USER");
		printf("%s:", user);
		g_data.cmd = readline("$ ");
		if (!g_data.cmd) // verificar ctr+d (EOF - free all - exit)
			break ;
		while (ft_check_quotes(g_data.cmd))
			g_data.cmd = ft_strjoin_free(g_data.cmd, readline("> "));
		add_history(g_data.cmd);
		g_data.cmd = ft_switch_inside_quotation(g_data.cmd);
		g_data.cmd_token = ft_strtrim(ft_strtok(g_data.cmd, "|<<>>;"), " ");
		while (g_data.cmd_token != NULL)
		{
			// g_data.cmd_token = ft_switch_inside_quotation(g_data.cmd_token);
			ft_add_token(g_data.cmd_token, g_data.cmd_type);
			free(g_data.cmd_token);
			g_data.cmd_token = ft_strtrim(ft_strtok(NULL, "|<<>>;"), " ");
		}
		// printf("\n------------- Token list -------------\n");
		// ft_print_token_list();
		// printf("\n--------------------------------------\n\n");
		ft_execute_token_list();
		ft_free_token_list(g_data.token_start, 1);
		ft_exit();
		free(g_data.cmd);
		free(user);
	}
	rl_clear_history();
}
