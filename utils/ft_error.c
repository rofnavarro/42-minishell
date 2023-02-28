/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/28 15:55:11 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *msg, int arg)
{
	printf("%s\n", msg);
	strerror(arg);
	exit(EXIT_FAILURE);
}

void	ft_exit(t_program *g_data)
{
	if (ft_strncmp(g_data->cmd, "exit", ft_strlen(g_data->cmd) - 1) == 0)
		g_data->stop = 1;
}
