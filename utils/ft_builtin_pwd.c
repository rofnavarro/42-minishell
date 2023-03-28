/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:20:25 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/20 16:54:58 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char *str, t_program *g_data)
{
	char	*buff;
	char	*cwd;

	buff = NULL;
	cwd = getcwd(buff, 0);
	if (!cwd)
		ft_error("Couldn't find the current path for the working directory!\n", \
				ENOENT);
	else
		printf("%s\n", cwd);
	free(cwd);
}
