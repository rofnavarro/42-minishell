/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/28 17:02:47 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *msg, int arg)
{
	printf("%s\n", msg);
	strerror(arg);
}

void	ft_exit(void)
{
	if (ft_strncmp(g_data.cmd, "exit", ft_strlen(g_data.cmd)) == 0 && \
		ft_strlen(g_data.cmd) == 4)
		g_data.stop = 1;
}
