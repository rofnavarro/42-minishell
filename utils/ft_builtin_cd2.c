/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:23:47 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/02 13:46:52 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_back(char *aux)
{
	char	*buff;
	char	*path;
	int		dir;

	dir = chdir("..");
	if (dir < 0)
	{
		ft_error(errno);
		return ;
	}
	buff = NULL;
	path = getcwd(buff, 0);
	ft_export_add_env(path, "PWD=");
	free(buff);
	free(path);
}

void	ft_cd_home(char *aux)
{
	char	*buff;
	char	**home;
	char	*path;
	int		i;

	i = -1;
	while (g_data.env[++i])
	{
		if (ft_strncmp(g_data.env[i], "HOME=", 5) == 0)
			break ;
	}
	home = ft_split(g_data.env[i], '=');
	chdir(home[1]);
	buff = NULL;
	path = getcwd(buff, 0);
	ft_export_add_env(path, "PWD=");
	ft_free_matrix(home);
	free(buff);
	free(path);
}

void	ft_cd_stay(char *aux)
{
	char	*buff;
	char	*path;

	buff = NULL;
	path = getcwd(buff, 0);
	ft_export_add_env(path, "PWD=");
	free(buff);
	free(path);
}
