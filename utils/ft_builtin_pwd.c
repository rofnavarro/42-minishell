/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:20:25 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/09 19:39:06 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char *str, char **envp)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "pwd", ft_strlen(str) - 1) == 0)
	{
		while (ft_strnstr(envp[i], "PWD=", 4) == 0)
			i++;
		printf("%s\n", envp[i] + 4);
	}
}
