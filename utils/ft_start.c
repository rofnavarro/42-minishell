/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:43:55 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/07 17:12:36 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_path(void)
{
	int	i;

	i = 0;
	if (!g_data.env)
		g_data.path = NULL;
	if (g_data.path)
		ft_free_matrix(g_data.path);
	while (g_data.env[i])
	{
		if (ft_strncmp(g_data.env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (i == ft_env_size(g_data.env))
		g_data.path = NULL;
	else
		g_data.path = (ft_split(g_data.env[i] + 5, ':'));
}

static void	get_env(char **envp)
{
	int	i;

	g_data.env = (char **)ft_env_calloc(ft_env_size(envp) + 1);
	i = 0;
	while (envp[i])
	{
		g_data.env[i] = ft_strdup(envp[i]);
		i++;
	}
}

void	ft_start(char **envp)
{
	get_env(envp);
	get_path();
}
