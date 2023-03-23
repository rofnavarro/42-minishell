/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:43:55 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/23 15:27:26 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_path(t_program *g_data, char **envp)
{
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	g_data->path = (ft_split(envp[i] + 5, ':'));
}

static void	get_env(t_program *g_data, char **envp)
{
	int	i;

	g_data->env = (char **)ft_env_calloc(ft_env_size(envp) + 1);
	i = 0;
	while (envp[i])
	{
		g_data->env[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	ft_start(char **envp, t_program *g_data)
{
	get_path(g_data, envp);
	get_env(g_data, envp);
}
