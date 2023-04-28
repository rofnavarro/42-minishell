/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 19:26:02 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/24 18:31:09 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_add_export(char *variable)
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
	g_data.exit_code = 0;
}

void	ft_export(char **cmd)
{
	if (g_data.export == NULL)
		get_export(g_data.env);
	if (cmd[1] == NULL)
		ft_print_export();
	else
	{
		ft_add_export(cmd[1]);
		ft_sort(g_data.export);
	}
}
