/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/02 13:46:43 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_add_env(char *var, char *var_name)
{
	char	*tmp;
	char	*tmp_exp;
	char	*exp;

	tmp = ft_strdup("export ");
	tmp_exp = ft_strjoin(tmp, var_name);
	free(tmp);
	exp = ft_strjoin(tmp_exp, var);
	free(tmp_exp);
	ft_add_var_env(exp);
	free(exp);
}

void	ft_check_cd_path(char *input_path)
{
	char	*buff;
	char	*path;
	int		dir;

	dir = chdir(input_path);
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

void	ft_cd(char *variable)
{
	char	*aux;
	char	*buff;
	char	*old_path;

	buff = NULL;
	aux = ft_substr(variable, 3, ft_strlen(variable) - 3);
	old_path = getcwd(buff, 0);
	ft_export_add_env(old_path, "OLDPWD=");
	if ((ft_strncmp(aux, "..", 2) == 0) && \
		(ft_strlen(aux) == ft_strlen("..")))
		ft_cd_back(aux);
	else if ((ft_strncmp(aux, "~", 1) == 0) && \
		(ft_strlen(aux) == ft_strlen("~")))
		ft_cd_home(aux);
	else if ((ft_strncmp(aux, ".", 1) == 0) && \
		(ft_strlen(aux) == ft_strlen(".")))
		ft_cd_stay(aux);
	else
		ft_check_cd_path(aux);
	free(aux);
	free(buff);
	free(old_path);
}
