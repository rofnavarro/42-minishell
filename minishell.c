/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/04 19:14:53 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	g_data;

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_error(errno);
		exit(errno);
	}
	g_data = (t_program){0};
	ft_start(envp);
	ft_loop();
	ft_free_data();
	printf("Minishell closed!\n");
	return (EXIT_SUCCESS);
}
