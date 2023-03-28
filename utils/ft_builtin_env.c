/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:25:37 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/28 18:17:47 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	var_exist(char *variable, int size)
{
	char	**full_export;
	char	**tmp_split;
	char	*tmp;
	int		i;

	tmp = ft_substr(variable, size, ft_strlen(variable) - size);
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

static void	replace_var_env(char *variable)
{
	char	**var_token;
	char	**tmp;
	char	*var_tmp;
	int		i;

	var_tmp = ft_substr(variable, 7, ft_strlen(variable) - 7);
	var_token = ft_split(var_tmp, '=');
	i = 0;
	while (g_data.env[i])
	{
		tmp = ft_split(g_data.env[i], '=');
		if (ft_strncmp(var_token[0], tmp[0], ft_strlen(var_token[0])) == 0)
		{
			g_data.env[i] = ft_strdup(var_tmp);
			ft_free_matrix(tmp);
			break ;
		}
		ft_free_matrix(tmp);
		i++;
	}
	ft_free_matrix(var_token);
	ft_free_matrix(tmp);
	free(var_tmp);
}

void	ft_add_var_env(char *variable)
{
	int		i;
	char	**new_env;

	if (!variable || !g_data.env)
		return ;
	if (var_exist(variable, 7) == TRUE)
	{
		replace_var_env(variable);
		return ;
	}
	new_env = ft_env_calloc(ft_env_size(g_data.env) + 2);
	i = -1;
	while (g_data.env[++i])
		new_env[i] = ft_strdup(g_data.env[i]);
	ft_free_matrix(g_data.env);
	new_env[i] = ft_substr(variable, 7, ft_strlen(variable) - 7);
	g_data.env = new_env;
}

void	ft_remove_var_env(char *variable)
{
	int		i;
	int		j;
	char	*aux;
	char	**new_env;
	char	**tmp;

	if (!variable || !g_data.env || ft_strlen(variable) < 6 || \
		var_exist(variable, 5))
		return ;
	aux = ft_substr(variable, 6, ft_strlen(variable) - 6);
	new_env = ft_env_calloc(ft_env_size(g_data.env) + 1);
	i = -1;
	j = 0;
	while (g_data.env[++i + j])
	{
		tmp = ft_split(g_data.env[i + j], '=');
		if (ft_strncmp(tmp[0], aux, ft_strlen(tmp[0])) == 0 && \
			(ft_strlen(tmp[0]) == ft_strlen(aux)))
			j = 1;
		if (g_data.env[i + j] == NULL)
		{
			ft_free_matrix(tmp);
			break ;
		}
		new_env[i] = ft_strdup(g_data.env[i + j]);
		ft_free_matrix(tmp);
	}
	free(aux);
	ft_free_matrix(g_data.env);
	g_data.env = new_env;
}
