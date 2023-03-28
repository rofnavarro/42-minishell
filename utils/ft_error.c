/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/28 16:41:49 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *msg, int arg)
{
	printf("%s\n", msg);
	strerror(arg);
	// exit(EXIT_FAILURE);
}

void	ft_exit(t_program *g_data)
{
	if (ft_strncmp(g_data->cmd, "exit", ft_strlen(g_data->cmd)) == 0 && \
		ft_strlen(g_data->cmd) == 4)
		g_data->stop = 1;
}
