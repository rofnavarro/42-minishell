/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/30 17:33:07 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export_add_env(char *var, char *var_name)
{
	char	**exp;

	exp = (char **)ft_env_calloc(2 + 1);
	exp[0] = ft_strdup("export ");
	exp[1] = ft_strjoin(var_name, var);
	ft_add_var_env(exp);
	ft_free_matrix(exp);
}

static void	ft_check_cd_path(char *input_path)
{
	char	*buff;
	char	*path;

	if (chdir(input_path) == -1)
	{
		perror(NULL);
		return ;
	}
	buff = NULL;
	path = getcwd(buff, 0);
	ft_export_add_env(path, "PWD=");
	ft_free_pointers(buff, path);
	g_data.exit_code = 0;
}

static void	ft_cd_home(void)
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
	if (g_data.env[i] == NULL)
		return ;
	home = ft_split(g_data.env[i], '=');
	buff = NULL;
	path = getcwd(buff, 0);
	if (path == NULL || chdir(home[1]) == -1)
	{
		perror(NULL);
		return ;
	}
	ft_export_add_env(path, "PWD=");
	ft_free_matrix(home);
	ft_free_pointers(buff, path);
	g_data.exit_code = 0;
}

void	ft_cd(char **cmd)
{
	char	*buff;
	char	*old_path;

	if (cmd[2])
		return(ft_error(1, "cd: too many arguments"));
	buff = NULL;
	old_path = getcwd(buff, 0);
	ft_export_add_env(old_path, "OLDPWD=");
	if ((ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0) && !cmd[1] && \
		ft_strlen(cmd[0]) == ft_strlen("cd"))
		ft_cd_home();
	else if (ft_strlen(cmd[0]) == ft_strlen("cd"))
	{
		if (ft_strncmp(cmd[1], "~", ft_strlen(cmd[1])) == 0)
			ft_cd_home();
		else
			ft_check_cd_path(cmd[1]);
	}
	free(buff);
	free(old_path);
}
