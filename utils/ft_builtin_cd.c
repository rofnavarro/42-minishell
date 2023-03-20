/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/20 16:29:21 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_old_dir(t_program *g_data)
{
	int	i;

	i = 0;
	while (g_data->env[i])
	{
		if (ft_strncmp(g_data->env[i], "PWD=", 4) == 0)
			return (g_data->env[i]);
		i++;
	}
}

void	ft_cd(char *str, t_program *g_data)
{
	char	*home;
	char	*old_dir;

	if (ft_strncmp(str, "cd", ft_strlen(str) - 1) == 0)
	{

		old_dir = get_old_dir(g_data);
		if (chdir(home) == 0)
		{
			printf("%s\n", home);
		}
		else
			printf("Couldn't find home directory\n");
		free(old_dir);
		// printf("%s\n", old_dir);
		// i = 0;
		// while (ft_strncmp(g_data->env[i], "PWD=", 4) != 0)
		// 	i++;
		// aux = ft_substr(g_data->env[i], 4, ft_strlen(g_data->env[i]) - 4);
		// g_data->env[i + 1] = ft_strjoin("OLDPWD=", aux);
		// free(aux);
		// printf("%s\n", g_data->env[i]);
		// printf("%s\n", g_data->env[i + 1]);
	}
	// free(buff);
}
