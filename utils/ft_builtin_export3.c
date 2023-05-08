/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:11:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/08 16:18:15 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sort(char **export)
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

void	ft_add_prefix(char **export)
{
	int		i;
	char	*tmp;

	i = -1;
	while (export[++i] != NULL)
	{
		tmp = ft_strjoin("declare -x ", export[i]);
		free(export[i]);
		export[i] = ft_strdup(tmp);
		free(tmp);
	}
}

void	ft_handle_export_quotes(char **export, int j)
{
	char	*tmp;
	char	*aux;
	char	*aux2;

	tmp = ft_substr(*export, 0, (j + 1));
	aux = ft_strjoin_free(tmp, "\"");
	tmp = ft_substr(*export, (j + 1), (ft_strlen(*export)));
	aux2 = ft_strjoin_free(tmp, "\"");
	tmp = ft_strjoin_free(aux, aux2);
	free(aux2);
	free(*export);
	*export = ft_strdup(tmp);
	free(tmp);
}

void	ft_put_value_quotes_matrix(char **export)
{
	int		i;
	int		j;

	i = -1;
	while (export[++i] != NULL)
	{
		j = 0;
		while (export[i][j] != '=' && export[i][j] != '\0')
			j++;
		if (export[i][j] != '\0')
		{
			if (export[i][j + 1] != '\"')
				ft_handle_export_quotes(&export[i], j);
		}
	}
}

void	get_export(char **env)
{
	int	i;

	if (g_data.export != NULL)
		ft_free_matrix(g_data.export);
	g_data.export = (char **)ft_env_calloc(ft_env_size(env) + 1);
	i = -1;
	while (env[++i])
		g_data.export[i] = ft_strdup(env[i]);
	if (ft_env_size(env) < 500)
		ft_sort(g_data.export);
	ft_add_prefix(g_data.export);
	ft_put_value_quotes_matrix(g_data.export);
}
