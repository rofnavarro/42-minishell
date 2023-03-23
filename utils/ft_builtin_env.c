/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:25:37 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/22 23:16:23 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	var_exist(char *var, t_program *g_data, int size)
{
	char	*new_var;
	int		i;
	int		j;

	new_var = ft_substr(var, size, ft_strlen(var) - size + 1);
	i = 0;
	while (new_var[i] != '=')
		i++;
	j = 0;
	while (g_data->env[j])
	{
		if (ft_strncmp(g_data->env[j], new_var, i - 1) == 0)
		{
			free(new_var);
			return (TRUE);
		}
		j++;
	}
	free(new_var);
	return (FALSE);
}

static void	replace_var_env(char *var, t_program *g_data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = ft_substr(var, 7, ft_strlen(var));
	while (tmp[i] != '=')
		i++;
	j = 0;
	while (ft_strncmp(tmp, g_data->env[j], i - 1) != 0)
		j++;
	g_data->env[j] = ft_strdup(tmp);
	free(tmp);
}

void	ft_add_var_env(char *new_variable, t_program *g_data)
{
	int		i;
	char	**new_env;

	if (!new_variable || !g_data->env)
		return ;
	if (var_exist(new_variable, g_data, 7) == TRUE)
	{
		replace_var_env(new_variable, g_data);
		return ;
	}
	new_env = ft_env_calloc(ft_env_size(g_data->env), 2);
	i = -1;
	while (g_data->env[++i])
		new_env[i] = ft_strdup(g_data->env[i]);
	ft_free_matrix(g_data->env);
	new_env[i] = ft_substr(new_variable, 7, ft_strlen(new_variable) - 6);
	g_data->env = new_env;
}

void	ft_remove_var_env(char *variable, t_program *g_data)
{
	int		i;
	int		j;
	char	*aux;
	char	**new_env;

	if (!variable || !g_data->env || ft_strlen(variable) < 6)
		return ;
	if (var_exist(variable, g_data, 6) == FALSE)
		return ;
	aux = ft_substr(variable, 6, ft_strlen(variable) - 5);
	new_env = ft_env_calloc(ft_env_size(g_data->env), 0);
	i = -1;
	j = 0;
	while (g_data->env[++i + j])
	{
		if (ft_strncmp(g_data->env[i + j], aux, ft_strlen(aux)) == 0)
			j = 1;
		if (g_data->env[i + j] == NULL)
			break ;
		new_env[i] = ft_strdup(g_data->env[i + j]);
	}
	free(aux);
	ft_free_matrix(g_data->env);
	g_data->env = new_env;
}
