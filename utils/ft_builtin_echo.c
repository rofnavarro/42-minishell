/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:19:30 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/05 15:23:48 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_find_print_var(char *dollar_var)
{
	int		i;
	char	**env_split;
	char	*aux;
	char	*tmp;

	tmp = ft_substr(dollar_var, 1, ft_strlen(dollar_var));
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
	int	i;

	if (ft_strlen(cmd[0]) < 4)
	{
		printf("\n");
		return ;
	}
	i = 1;
	while (cmd[i] != NULL)
	{
		if (cmd[i][0] == '$' && cmd[i][1] == '?')
			printf("%d\n", g_data.exit_code);
		else if (cmd[i][0] == '$' && ft_isprint(cmd[i][1]) != 0)
			ft_find_print_var(cmd[i]);
		else if ((ft_strncmp(cmd[1], "-n", ft_strlen("-n")) == 0) && \
					cmd[i + 1] != NULL)
		{
			printf("%s", cmd[i + 1]);
			if (i + 1 >= 2 && cmd[i + 2] != NULL)
				printf(" ");
		}
		else if (ft_strncmp(cmd[1], "-n", ft_strlen("-n") != 0))
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1] != NULL)
				printf(" ");
			else
				printf("\n");
		}
		g_data.exit_code = 0;
		i++;
	}
}
