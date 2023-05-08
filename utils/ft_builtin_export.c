/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:10:56 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/08 17:21:21 by rferrero         ###   ########.fr       */
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

void	exportation(char *cmd)
{
	char	*tmp[2];

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
}
