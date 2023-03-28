/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/28 17:07:39 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program g_data;

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_error("Error. Don't need arguments to start minishell.", EINVAL);
		exit(EINVAL);
	}
	g_data = (t_program){0};
	ft_start(envp);
	ft_loop();
	printf("Minishell closed!\n");
	return (EXIT_SUCCESS);
}
