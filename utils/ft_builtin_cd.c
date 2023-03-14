/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/14 16:46:49 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char *str, t_program *g_data)
{
	int		i;
	char	*aux;

	if (ft_strncmp(str, "cd", ft_strlen(str) - 1) == 0)
	{
		i = 0;
		while (ft_strncmp(g_data->env[i], "PWD=", 4) != 0)
			i++;
		aux = ft_substr(g_data->env[i], 4, ft_strlen(g_data->env[i]) - 4);
		g_data->env[i + 1] = ft_strjoin("OLDPWD=", aux);
		printf("%s\n", g_data->env[i]);
		printf("%s\n", g_data->env[i + 1]);
	}
}
