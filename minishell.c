/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/08 00:54:46 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_data;

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		printf("Minishell don't need any arguments to run\n");
		exit(EXIT_FAILURE);
	}
	g_data = (t_program){0};
	ft_start(envp);
	ft_loop();
	ft_free_data();
	printf("Minishell closed!\n");
	return (EXIT_SUCCESS);
}
