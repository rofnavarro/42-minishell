/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/05 15:16:51 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export_add_env(char *var, char *var_name)
{
	char	*tmp;
	char	**exp;

	exp = (char **)ft_env_calloc(2 + 1);
	exp[0] = ft_strdup("export ");
	tmp = ft_strjoin(exp[0], var_name);
	exp[1] = ft_strjoin(tmp, var);
	ft_add_var_env(exp);
	free(tmp);
	ft_free_matrix(exp);
}

static void	ft_check_cd_path(char *input_path)
{
	char	*buff;
	char	*path;
	int		dir;

	dir = chdir(input_path);
	if (dir < 0)
		return (ft_error(errno));
	buff = NULL;
	path = getcwd(buff, 0);
	ft_export_add_env(path, "PWD=");
	free(buff);
	free(path);
}

static void	ft_cd_home(void)
{
	char	*buff;
	char	**home;
	char	*path;
	int		i;
	int		dir;

	i = -1;
	while (g_data.env[++i])
	{
		if (ft_strncmp(g_data.env[i], "HOME=", 5) == 0)
			break ;
	}
	home = ft_split(g_data.env[i], '=');
	dir = chdir(home[1]);
	if (dir < 0)
		return (ft_error(errno));
	buff = NULL;
	path = getcwd(buff, 0);
	if (path < 0)
		return (ft_error(errno));
	ft_export_add_env(path, "PWD=");
	ft_free_matrix(home);
	free(buff);
	free(path);
}

void	ft_cd(char **cmd)
{
	char	*buff;
	char	*old_path;

	buff = NULL;
	old_path = getcwd(buff, 0);
	ft_export_add_env(old_path, "OLDPWD=");
	if ((ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0) && !cmd[1])
		ft_cd_home();
	else
	{
		if (ft_strncmp(cmd[1], "~", ft_strlen(cmd[1])) == 0)
			ft_cd_home();
		else
			ft_check_cd_path(cmd[1]);
	}
	free(buff);
	free(old_path);
}
