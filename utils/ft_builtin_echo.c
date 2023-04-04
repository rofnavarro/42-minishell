/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:19:30 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/04 17:33:23 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_find_print_var(char *dollar_var)
{
	int		i;
	char	**env_split;
	char	*aux;
	char	*tmp;

	tmp = ft_substr(dollar_var, 1, ft_strlen(dollar_var) - 1);
	if (var_exist(tmp) == TRUE)
	{
		i = 0;
		while (g_data.env[i])
		{
			env_split = ft_split(g_data.env[i], '=');
			if (ft_strncmp(tmp, env_split[0], ft_strlen(env_split[0])) == 0)
				printf("%s\n", env_split[1]);
			ft_free_matrix(env_split);
			i++;
		}
		free(tmp);
	}
	else
	{
		printf("\n");
		free(tmp);
	}
}

void	ft_echo(char **cmd)
{
	if (ft_strlen(cmd[0]) < 4)
	{
		printf("\n");
		return ;
	}
	if (cmd[1][0] == '$' && ft_isalnum(cmd[1][1]) != 0)
		ft_find_print_var(cmd[1]);
	else if (ft_strncmp(cmd[1], "-n ", ft_strlen("-n ")) != 0)
		printf("%s\n", cmd[1]);
	else
		printf("%s", cmd[1]);
}
