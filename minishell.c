/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/18 22:55:17 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_program data;

int	main(int argc, char **argv)
{

	data.stop = 0;
	if (argc != 1)
		ft_error("Error. You don't need any arguments to start minishell.");
	while (data.stop == 0)
	{
		printf("hell:$ ");

		fgets(data.cmd, 100, stdin);
		data.cmd[ft_strlen(data.cmd) - 1] = '\0';

		if(ft_strncmp(data.cmd, "exit", ft_strlen(data.cmd) - 1) == 0)
			data.stop = 1;
	}

	printf("Minishell closed!\n");
	return (EXIT_SUCCESS);
}
