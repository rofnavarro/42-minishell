/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/29 17:01:24 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char *variable)
{
	char	*path;
	char	*aux;
	char	*buff;

	buff = NULL;
	aux = ft_substr(variable, 3, ft_strlen(variable) - 3);
	if (ft_strncmp(aux, "..", 1) == 0)
		chdir("..");
	path = getcwd(buff, 0);
	printf("\n\n%s\n\n", path);
	free(path);
	free(aux);
}
