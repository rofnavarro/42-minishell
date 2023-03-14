/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:25:37 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/14 18:20:35 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_env(char *new_variable, t_program *g_data)
{
	int		i;
	char	**old_env;

	i = 0;
	if (ft_strncmp(new_variable, "export", 6) == 0)
	{
		old_env = g_data->env;
		while (old_env[i])
			i++;
		g_data->env = (char **)ft_calloc(sizeof(char *), i + 2);
		i = 0;
		while (old_env[i])
		{
			g_data->env[i] = ft_strdup(old_env[i]);
			i++;
		}
		ft_free_matrix(old_env);
		g_data->env[i] = ft_substr(new_variable, 7, ft_strlen(new_variable) - 6);
	}
}

// void	ft_remove_env(char *new_variable, t_program *g_data)
// {
// 	int		i;
// 	char	*aux;
// 	char	**old_env;

// 	i = 0;
// 	if (ft_strncmp(new_variable, "unset", 5) == 0)
// 	{
// 		old_env = g_data->env;
// 		aux = ft_substr(new_variable, 6, ft_strlen(new_variable) - 5);
// 		while (ft_strncmp(aux, old_env[i], ft_strlen(aux)) != 0)
// 			i++;
// 	}
// }
