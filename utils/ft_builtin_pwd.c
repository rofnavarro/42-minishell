/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:20:25 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/02 15:09:40 by rferrero         ###   ########.fr       */
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
		ft_error(errno);
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
