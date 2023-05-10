/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:10:56 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/10 09:04:07 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(char **cmd)
{
	int		i;

	if (g_data.export[0] == NULL)
		get_export(g_data.env);
	if (!cmd[1])
		ft_print_export();
	else
	{
		i = 0;
		while (cmd[++i])
			exportation(cmd[i]);
	}
	ft_sort(g_data.export);
}

int	check_export_validation(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
	{
		printf("minishell: export: '%s': not a valid identifier\n", str);
		g_data.exit_code = 1;
		return (FALSE);
	}
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalpha(str[i]) == 0)
		{
			printf("minishell: export: '%s': not a valid identifier\n", str);
			g_data.exit_code = 1;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	exportation(char *cmd)
{
	char	*tmp[2];

	if (check_export_validation(cmd) == FALSE)
		return ;
	if (is_var_assigned(cmd) == TRUE)
	{
		if (var_exist_export(cmd) == TRUE)
			replace_var_export(cmd);
		else
			ft_add_export(cmd);
		tmp[0] = "export";
		tmp[1] = ft_strdup(cmd);
		ft_add_var_env(tmp);
		free(tmp[1]);
	}
	else
	{
		if (var_exist_export(cmd) == TRUE)
			replace_var_export(cmd);
		else
			ft_add_export(cmd);
	}
	g_data.exit_code = 0;
}

void	ft_remove_var_export(char *var)
{
	int		i;
	int		j;
	char	*new_var;
	char	**new_export;

	new_export = ft_env_calloc(ft_env_size(g_data.export) + 1);
	new_var = ft_strjoin("declare -x ", var);
	i = -1;
	j = 0;
	while (g_data.export[++i + j])
	{
		if (ft_strncmp(new_var, g_data.export[i + j], ft_strlen(new_var)) == 0
			&& (g_data.export[i + j][ft_strlen(new_var)] == '='
			|| g_data.export[i + j][ft_strlen(new_var)] == '\0'))
			j = 1;
		if (g_data.export[i + j] == NULL)
			break ;
		new_export[i] = ft_strdup(g_data.export[i + j]);
	}
	free(new_var);
	ft_free_matrix(g_data.export);
	g_data.export = new_export;
}
