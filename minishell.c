/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:19:46 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/28 16:42:57 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_error("Error. Don't need arguments to start minishell.", EINVAL);
		exit(EXIT_FAILURE);
	}
	ft_init(void);
	ft_start(envp);
	ft_loop(void);
	printf("Minishell closed!\n");
	return (EXIT_SUCCESS);
}
