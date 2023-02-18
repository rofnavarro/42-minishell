/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/18 19:57:31 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv)
{
	t_program data;

	if (argc != 1)
		ft_error("Error. You don't need any arguments to start minishell.");
	while (1)
	{
		printf("rshell> ");
		fflush(stdout);

		fgets(data.cmd, 100, stdin);
		data.cmd[ft_strlen(data.cmd) - 1] = '\0';

		if(ft_strncmp(data.cmd, "exit", ft_strlen(data.cmd) - 1) == 0)
			break;
	}

	printf("SUCESSO!\n");
	return (EXIT_SUCCESS);
}
