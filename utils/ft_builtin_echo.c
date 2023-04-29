/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:19:30 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/28 22:34:37 by rferrero         ###   ########.fr       */
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
				printf("%s", env_split[1]);
			ft_free_matrix(env_split);
			i++;
		}
	}
	free(tmp);
}

static void	ft_echo_class(char **cmd, int i)
{
	if (cmd[i][0] == '\n')
		return ;
	else
		printf("%s", cmd[i]);
}

void	ft_echo(char **cmd)
{
	int		i;
	char	*tmp;

	if (ft_strlen(cmd[0]) == 4 && cmd[1] == NULL)
	{
		printf("\n");
		return ;
	}
	i = 0;
	if (ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) == 0)
		i = 1;
	while (cmd[++i])
	{
		ft_echo_class(cmd, i);
		if (cmd[i + 1] != NULL)
			printf(" ");
	}
	if (ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) != 0)
		printf("\n");
	g_data.exit_code = 0;
}
