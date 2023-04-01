/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/31 21:44:45 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_cd_back(char *aux)
{
	char	*buff;
	char	*path;

	buff = NULL;
	chdir("..");
	path = getcwd(buff, 0);
	ft_add_var_env(path);
	free(path);
	free(buff);
}

static void	ft_cd_stay(char *aux)
{
	char	*buff;
	char	*path;

	buff = NULL;
	path = getcwd(buff, 0);
	ft_add_var_env(path);
	free(path);
	free(buff);
}

void	ft_cd(char *variable)
{
	char	*aux;
	char	*buff;
	char	*old_path;

	buff = NULL;
	aux = ft_substr(variable, 3, ft_strlen(variable) - 3);
	old_path = getcwd(buff, 0);
	if ((ft_strncmp(aux, "..", 2) == 0) && (ft_strlen(aux) == ft_strlen("..")))
		ft_cd_back(aux);
	else if ((ft_strncmp(aux, ".", 1) == 0) && (ft_strlen(aux) == ft_strlen(".")))
		ft_cd_stay(aux);
	printf("\n\n%s\n\n", old_path);
	free(aux);
	free(old_path);
	free(buff);
}
