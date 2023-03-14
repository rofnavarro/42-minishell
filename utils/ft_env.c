/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:25:37 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/14 18:03:02 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_env(char *new_variable, t_program *g_data)
{
	int		i;
	char	**new_env;

	i = 0;
	if (ft_strncmp(new_variable, "export", 6) == 0)
	{
		new_env = g_data->env;
		while (new_env[i])
			i++;
		g_data->env = (char **)ft_calloc(sizeof(char *), i + 2);
		i = 0;
		while (new_env[i])
		{
			g_data->env[i] = ft_strdup(new_env[i]);
			i++;
		}
		ft_free_matrix(new_env);
		g_data->env[i] = ft_substr(new_variable, 7, ft_strlen(new_variable) - 6);
	}
}