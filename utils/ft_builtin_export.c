/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:11:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/18 18:49:33 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_sort(char **export)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (export[++i + 1] != NULL)
	{
		if (ft_strncmp(export[i], export[i + 1], ft_strlen(export[i])) > 0)
		{
			tmp = ft_strdup(export[i]);
			export[i] = ft_strdup(export[i + 1]);
			export[i + 1] = ft_strdup(tmp);
			i = -1;
			free(tmp);
		}
	}
}

static void	ft_add_prefix(char **export)
{
	int		i;
	char	*tmp[2];

	i = -1;
	while (export[++i] != NULL)
	{
		tmp[0] = ft_strdup("declare -x ");
		tmp[1] = ft_strdup(export[i]);
		free(export[i]);
		export[i] = ft_strjoin(tmp[0], tmp[1]);
		ft_free_matrix(tmp);		
	}
}

void	get_export(char **env)
{
	int	i;

	g_data.export = (char **)ft_env_calloc(ft_env_size(env) + 1);
	i = -1;
	while (env[++i])
		g_data.export[i] = ft_strdup(env[i]);
	ft_sort(g_data.export);
	ft_add_prefix(g_data.export);
	// for (int z = 0; g_data.export[z] != NULL; z++)
	// 	printf("%s\n", g_data.export[z]);
}
