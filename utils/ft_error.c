/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:26:18 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/02 14:43:11 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(int arg)
{
	// printf("Errno : %d\n", arg);
	
	// mudar para o comando que estiver sendo usado
	printf("%s : ", g_data.cmd);
	strerror(arg);
	printf("%s\n", strerror(arg));
}

void	ft_exit(void)
{
	if (ft_strncmp(g_data.cmd, "exit", ft_strlen(g_data.cmd)) == 0 && \
		ft_strlen(g_data.cmd) == 4)
		g_data.stop = 1;
}
