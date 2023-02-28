/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/28 17:05:28 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_program	g_data;

	g_data.stop = 0;
	if (argc != 1)
		ft_error("Error. Don't need arguments to start minishell.", EINVAL);
	ft_start(envp, &g_data);
	while (g_data.stop == 0)
	{
		g_data.cmd = readline("hell$: ");
		add_history(g_data.cmd);
		ft_exit(&g_data);
	}
	printf("Minishell closed!\n");
	return (EXIT_SUCCESS);
}
