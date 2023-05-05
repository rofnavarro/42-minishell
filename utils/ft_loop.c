/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/04 20:54:36 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(void)
{	
	while (g_data.stop == 0)
	{
		ft_loop_start();
		if (ft_check_eof_cmd())
			break ;
		while (ft_check_quotes(g_data.cmd))
			ft_handle_inclosed_quotes();
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
		if (ft_check_empty_line())
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
	if (!g_data.user)
		g_data.user = ft_strdup("unkwown");
	g_data.rl_text = ft_strjoin(g_data.user, ":$ ");
	g_data.cmd = readline(g_data.rl_text);
	free(g_data.rl_text);
}

int	ft_check_empty_line(void)
{
	if (!g_data.token_start)
	{
		ft_free_loop();
		return (1);
	}
	return (0);
}

int	ft_check_eof_cmd(void)
{
	if (!g_data.cmd)
	{
		printf("exit\n");
		ft_free_loop();
		return (1);
	}
	return (0);
}
