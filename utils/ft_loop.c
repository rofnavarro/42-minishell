/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/28 16:21:14 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(t_program *g_data)
{
	while (g_data->stop == 0)
	{
		g_data->cmd = readline("hell$: ");
		if (!g_data->cmd) 		// verificar ctr+d (EOF - free all - exit)
			break ;
		while (ft_check_quotes(g_data->cmd))
			g_data->cmd = ft_strjoin_free(g_data->cmd, readline("> "));
		add_history(g_data->cmd);

		is_builtin(g_data->cmd, g_data);
		g_data->cmd = ft_switch_inside_quotation(g_data->cmd);
		g_data->cmd_token = ft_strtrim(ft_strtok(g_data->cmd, "|<<>", g_data)," ");
		while (g_data->cmd_token != NULL)
		{
			g_data->cmd_token = ft_switch_inside_quotation(g_data->cmd_token);
			ft_add_token(g_data, g_data->cmd_token, g_data->cmd_type);
			g_data->cmd_token = ft_strtrim(ft_strtok(NULL, "|<<>", g_data), " ");
		}
		ft_print_token_list(g_data);
		ft_execute_token_list(g_data);
		ft_free_token_list(g_data, g_data->token_start, 1);
		ft_exit(g_data);
		free(g_data->cmd);
	}
	ft_free_data(g_data);
	rl_clear_history();
}
