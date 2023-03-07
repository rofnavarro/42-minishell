/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/07 17:26:21 by rferrero         ###   ########.fr       */
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

		g_data->cmd_token = ft_strtok(g_data->cmd, "|");
		printf("%s\n", g_data->cmd_token);
		// while (g_data->cmd_token != NULL)
		// {
		// 	printf("%s\n", g_data->cmd_token);
		// 	g_data->cmd_token = ft_strtok(NULL, "|");
		// }
		ft_exit(g_data);
	}
	//ft_free_matrix(g_data->env);
	ft_free_matrix(g_data->path);
}
