/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/22 17:25:05 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_program	g_data;

int	main(int argc, char **argv, char **envp)
{
	g_data.stop = 0;
	if (argc != 1)
		ft_error("Error. Don't need arguments to start minishell.", EINVAL);
	g_data.env = ft_start(envp);
	while (g_data.stop == 0)
	{
		printf("hell:$ ");
		fgets(g_data.cmd, 100, stdin);
		g_data.cmd[ft_strlen(g_data.cmd) - 1] = '\0';
		if (ft_strncmp(g_data.cmd, "exit", ft_strlen(g_data.cmd) - 1) == 0)
			g_data.stop = 1;
	}
	printf("Minishell closed!\n");
	return (EXIT_SUCCESS);
}
