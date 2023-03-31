/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/31 20:56:51 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_cd_back(char *aux)
{
	char	*buff;
	char	*buff2;
	char	*path;
	char	*old_path;

	buff = NULL;
	if ((ft_strncmp(aux, "..", 2) == 0) && (ft_strlen(aux) == ft_strlen("..")))
	{
		old_path = getcwd(buff, 0);
		chdir("..");
		path = getcwd(buff2, 0);
	}
	printf("\n\n%s\n\n", old_path);
	printf("\n\n%s\n\n", path);
	free(buff);
	free(buff2);
	free(path);
	free(old_path);
}

static void	ft_cd_stay(char *aux)
{
	char	*buff;
	char	*buff2;
	char	*path;
	char	*old_path;

	buff = NULL;
	buff2 = NULL;
	if ((ft_strncmp(aux, ".", 1) == 0) && (ft_strlen(aux) == ft_strlen(".")))
	{
		old_path = getcwd(buff, 0);
		path = getcwd(buff2, 0);
	}
	printf("\n\n%s\n\n", old_path);
	printf("\n\n%s\n\n", path);
	free(buff);
	free(buff2);
	free(path);
	free(old_path);
}

void	ft_cd(char *variable)
{
	char	*aux;

	aux = ft_substr(variable, 3, ft_strlen(variable) - 3);
	ft_cd_back(aux);
	ft_cd_stay(aux);
	free(aux);
}
