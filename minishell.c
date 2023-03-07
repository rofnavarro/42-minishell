/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/07 19:39:19 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_program	g_data;

	if (argc != 1)
		ft_error("Error. Don't need arguments to start minishell.", EINVAL);
	ft_init(&g_data);
	ft_start(envp, &g_data);
	ft_loop(&g_data);
	printf("Minishell closed!\n");
	return (EXIT_SUCCESS);
}
