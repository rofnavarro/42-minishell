/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/19 13:59:29 by rferrero         ###   ########.fr       */
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
	if (ft_strncmp(g_data.cmd, "exit", ft_strlen(g_data.cmd)) == 0)
		g_data.stop = 1;
}
