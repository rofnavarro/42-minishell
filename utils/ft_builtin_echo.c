/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:19:30 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/02 20:08:14 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *cmd)
{
	char	*aux;
	char	*aux_no_line;

	if (ft_strlen(cmd) <= 5)
	{
		printf("\n");
		return ;
	}
	aux = ft_substr(cmd, 5, ft_strlen(cmd) - 5);
	if (ft_strncmp(aux, "-n ", ft_strlen("-n ")) != 0)
		printf("%s\n", aux);
	else
	{
		aux_no_line = ft_substr(aux, 3, ft_strlen(aux) - 3);
		printf("%s", aux_no_line);
		free(aux_no_line);
	}
	free(aux);
}
