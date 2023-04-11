/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:20:25 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/11 03:10:03 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char *str)
{
	char	*buff;
	char	*cwd;

	buff = NULL;
	cwd = getcwd(buff, 0);
	if (!cwd)
	{
		perror(NULL);
		ft_error(1, "getcwd falhou\n");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
