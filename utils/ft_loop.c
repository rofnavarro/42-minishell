/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/05 01:54:30 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_loop(t_program *g_data)
{
	while (g_data->stop == 0)
	{
		g_data->cmd = readline("hell$: ");
		add_history(g_data->cmd);

		g_data->cmd_token = ft_strtok(g_data->cmd, " ");
		while (g_data->cmd_token != NULL)
		{
			printf("%s\n", g_data->cmd_token);
			g_data->cmd_token = ft_strtok(NULL, " ");
		}

		ft_exit(g_data);
	}
}
