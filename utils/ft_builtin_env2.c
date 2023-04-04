/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:44:33 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/29 15:14:19 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i] && *env != NULL)
		i++;
	return (i);
}

char	**ft_env_calloc(int size)
{
	char	**ret;

	ret = (char **)ft_calloc(sizeof(char *), size);
	return (ret);
}

void	ft_print_env(char *cmd)
{
	int	i;

	i = 0;
	if (!g_data.env || !cmd || ft_strlen(cmd) < 3 || ft_strlen(cmd) > 3)
		return ;
	while (g_data.env[i])
	{
		printf("%s\n", g_data.env[i]);
		i++;
	}
}

void	ft_find_var(char *find_var, char *env_var, int *found)
{
	if (ft_strncmp(env_var, find_var, ft_strlen(env_var)) == 0 && \
		ft_strlen(env_var) == ft_strlen(find_var))
		*found = 1;
}
