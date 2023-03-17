/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:25:37 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/17 16:11:04 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static char	**ft_env_calloc(int size, int diff)
{
	char	**ret;

	ret = (char **)ft_calloc(sizeof(char *), size + diff);
	return (ret);
}

void	ft_add_env(char *new_variable, t_program *g_data)
{
	int		i;
	char	**new_env;

	// transformar esse 6 em token comand size
	if (ft_strncmp(new_variable, "export", 6) == 0)
	{
		new_env = ft_env_calloc(ft_env_size(g_data->env), 2);
		i = -1;
		while (g_data->env[++i])
			new_env[i] = ft_strdup(g_data->env[i]);
		ft_free_matrix(g_data->env);
		new_env[i] = ft_substr(new_variable, 7, ft_strlen(new_variable) - 6);
		g_data->env = new_env;
	}
}

// void	ft_remove_env(char *new_variable, t_program *g_data)
// {
// 	int		i;
// 	char	*aux;
// 	char	**new_env;

// 	// transformar esse 5 em token command size
// 	if (ft_strncmp(new_variable, "unset", 5) == 0)
// 	{
// 		// new_env = ft_env_calloc(ft_env_size(g_data->env), -1);
// 		// aux = ft_substr_free(new_variable, 6, ft_strlen(new_variable) - 6);
// 		new_env = ft_env_calloc(ft_env_size(g_data->env), -1);
// 		aux = ft_substr(new_variable, 6, ft_strlen(new_variable) - 5);
// 		i = 0;
// 		while (g_data->env[i])
// 		{
// 			if (ft_strncmp(aux, g_data->env[i], ft_strlen(aux)) != 0)
// 				new_env[i] = ft_strdup(g_data->env[i]);
// 			i++;
// 		}
// 		ft_free_matrix(g_data->env);
// 		g_data->env = new_env;
// 		free(aux);
// 		// free(new_env);
// 	}
// }
