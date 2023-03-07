/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/07 20:10:38 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(t_program *g_data)
{
	while (g_data->stop == 0)
	{
		g_data->cmd = readline("hell$: ");
		// verificar ctr+d (EOF - free all - exit)
		add_history(g_data->cmd);
		g_data->cmd_token = ft_strtok(g_data->cmd, "|><");
		while (g_data->cmd_token != NULL)
		{
			//ft_add_token(g_data->cmd_token, g_data->cmd_type);
			printf("%s\n", g_data->cmd_token);
			g_data->cmd_token = ft_strtok(NULL, "|><");
		}
		ft_exit(g_data);
		free(g_data->cmd);
	}
	//ft_free_matrix(g_data->env);
	ft_free_matrix(g_data->path);
	//ft_free_token_list();
	rl_clear_history();
}
