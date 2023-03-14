/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:20:25 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/14 16:38:29 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char *str, t_program *g_data)
{
	int		i;
	char	*aux;

	if (ft_strncmp(str, "pwd", ft_strlen(str) - 1) == 0)
	{
		i = 0;
		while (ft_strncmp(g_data->env[i], "PWD=", 4) != 0)
			i++;
		aux = ft_substr(g_data->env[i], 4, ft_strlen(g_data->env[i]));
		printf("%s\n", aux);
		free(aux);
	}
}
