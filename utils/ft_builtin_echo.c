/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:19:30 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/02 22:04:08 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_find_print_var(char *dollar_var)
{
	int		i;
	char	**env_split;
	char	*aux;

	if (var_exist(dollar_var, 1) == TRUE)
	{
		i = 0;
		aux = ft_substr(dollar_var, 1, ft_strlen(dollar_var) - 1);
		while (g_data.env[i])
		{
			env_split = ft_split(g_data.env[i], '=');
			if (ft_strncmp(aux, env_split[0], ft_strlen(env_split[0])) == 0)
				printf("%s\n", env_split[1]);
			ft_free_matrix(env_split);
			i++;
		}
		free(aux);
	}
	else
		printf("\n");
}

void	ft_echo(char *cmd)
{
	char	*aux;
	char	*aux_no_line;

	if (ft_strlen(cmd) <= 5)
	{
		printf("\n");
		return ;
	}
	aux = ft_substr(cmd, 5, ft_strlen(cmd) - 5);
	if (aux[0] == '$' && ft_isalpha(aux[1]) > 0)
		ft_find_print_var(aux);
	else if (ft_strncmp(aux, "-n ", ft_strlen("-n ")) != 0)
		printf("%s\n", aux);
	else
	{
		aux_no_line = ft_substr(aux, 3, ft_strlen(aux) - 3);
		printf("%s", aux_no_line);
		free(aux_no_line);
	}
	free(aux);
}
