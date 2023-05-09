/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:25:37 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/09 16:42:46 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_var_env(char *variable)
{
	char	**var_token;
	char	**tmp;
	int		i;

	var_token = ft_split(variable, '=');
	i = 0;
	while (g_data.env[i])
	{
		tmp = ft_split(g_data.env[i], '=');
		if (ft_strncmp(var_token[0], tmp[0], ft_strlen(var_token[0])) == 0)
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strdup(variable);
			ft_free_matrix(tmp);
			break ;
		}
		ft_free_matrix(tmp);
		i++;
	}
	ft_free_matrix(var_token);
	g_data.exit_code = 0;
}

int	var_exist(char *variable)
{
	char	**full_export;
	char	**tmp_split;
	char	*tmp;
	int		i;

	tmp = ft_strdup(variable);
	full_export = ft_split(tmp, '=');
	i = 0;
	free(tmp);
	while (g_data.env[i])
	{
		tmp_split = ft_split(g_data.env[i], '=');
		if (ft_strncmp(full_export[0], tmp_split[0], \
			ft_strlen(tmp_split[0]) + 1) == 0)
		{
			ft_free_matrix(tmp_split);
			ft_free_matrix(full_export);
			return (TRUE);
		}
		ft_free_matrix(tmp_split);
		i++;
	}
	ft_free_matrix(full_export);
	return (FALSE);
}

void	ft_add_var_env(char **variable)
{
	int		i;
	char	**new_env;

	if (!variable[1] || !g_data.env)
		return ;
	if (var_exist(variable[1]) == TRUE)
	{
		replace_var_env(variable[1]);
		return ;
	}
	new_env = ft_env_calloc(ft_env_size(g_data.env) + 2);
	i = -1;
	while (g_data.env[++i])
		new_env[i] = ft_strdup(g_data.env[i]);
	new_env[i] = ft_strdup(variable[1]);
	ft_free_matrix(g_data.env);
	g_data.env = new_env;
	g_data.exit_code = 0;
}

void	ft_remove_var_env(char *variable)
{
	int		i;
	int		j;
	char	**new_env;

	new_env = ft_env_calloc(ft_env_size(g_data.env) + 1);
	i = -1;
	j = 0;
	while (g_data.env[++i + j])
	{
		if (ft_strncmp(variable, g_data.env[i + j], ft_strlen(variable)) == 0
			&& g_data.env[i + j][ft_strlen(variable)] == '=')
			j = 1;
		if (g_data.env[i + j] == NULL)
			break ;
		new_env[i] = ft_strdup(g_data.env[i + j]);
	}
	ft_free_matrix(g_data.env);
	g_data.env = new_env;
}
