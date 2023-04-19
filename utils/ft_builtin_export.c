/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:11:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/19 02:08:52 by coder            ###   ########.fr       */
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
			free(export[i]);
			export[i] = ft_strdup(export[i + 1]);
			free(export[i + 1]);
			export[i + 1] = ft_strdup(tmp);
			free(tmp);
			i = -1;
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
		free(tmp[0]);
		free(tmp[1]);
	}
}

static void	ft_put_value_quotes(char **export)
{
	int		i;
	char	**tmp;
	char	*aux;

	i = -1;
	while (export[++i] != NULL)
	{
		tmp = ft_split(export[i], '=');
		free(export[i]);
		aux = ft_strjoin("\"", tmp[1]);
		free(tmp[1]);
		tmp[1] = ft_strjoin(aux, "\"");
		free(aux);
		aux = ft_strjoin(tmp[0], "=");
		export[i] = ft_strjoin(aux, tmp[1]);
		free(aux);
		ft_free_matrix(tmp);
	}
}

void	ft_print_export()
{
	int	i;

	i = -1;
	while (g_data.export[++i] != NULL)
		printf("%s\n", g_data.export[i]);
	g_data.exit_code = 0;
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
	ft_put_value_quotes(g_data.export);
}
