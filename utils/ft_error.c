/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/11 03:08:55 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(int arg, char *msg)
{
	g_data.exit_code = arg;
	printf("%s\n", msg);
}

void	ft_exit(void)
{
	if (ft_strncmp(g_data.cmd, "exit", ft_strlen(g_data.cmd)) == 0 && \
		ft_strlen(g_data.cmd) == 4)
		g_data.stop = 1;
}
