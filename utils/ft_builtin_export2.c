/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:26:02 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/08 17:17:00 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(void)
{
	int	i;

	i = -1;
	while (g_data.export[++i] != NULL)
		printf("%s\n", g_data.export[i]);
	g_data.exit_code = 0;
}

void	ft_add_export(char *variable)
{
	int		i;
	char	**new_export;

	new_export = ft_env_calloc(ft_env_size(g_data.export) + 2);
	i = -1;
	while (g_data.export[++i])
		new_export[i] = ft_strdup(g_data.export[i]);
	new_export[i] = ft_strjoin("declare -x ", variable);
	ft_free_matrix(g_data.export);
	g_data.export = new_export;
	ft_put_value_quotes_matrix(g_data.export);
	g_data.exit_code = 0;
}

int	var_exist_export(char *var)
{
	int		i;
	int		j;
	char	*new_var;

	new_var = ft_strjoin("declare -x ", var);
	j = 0;
	while (new_var[j] != '=' && new_var[j] != '\0')
		j++;
	i = -1;
	while (g_data.export[++i])
	{
		if (ft_strncmp(g_data.export[i], new_var, j) == 0)
		{
			free(new_var);
			return (TRUE);
		}
	}
	free(new_var);
	return (FALSE);
}

void	replace_var_export(char *var)
{
	int		i;
	int		j;
	char	*new_var;

	new_var = ft_strjoin("declare -x ", var);
	j = 0;
	while (new_var[j] != '=' && new_var[j] != '\0')
		j++;
	i = -1;
	while (g_data.export[++i])
	{
		if (ft_strncmp(g_data.export[i], new_var, j) == 0)
		{
			free(g_data.export[i]);
			g_data.export[i] = ft_strdup(new_var);
		}
	}
	free(new_var);
	ft_put_value_quotes_matrix(g_data.export);
}
