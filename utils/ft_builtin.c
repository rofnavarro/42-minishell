/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:14:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/02 12:58:35 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var_assigned(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	is_builtin(char *str)
{
	if (ft_strncmp(str, "env", ft_strlen(str) - 1) == 0)
		ft_print_env(str);
	else if (ft_strncmp(str, "export ", 7) == 0 && is_var_assigned(str) == TRUE)
		ft_add_var_env(str);
	else if (ft_strncmp(str, "unset ", 6) == 0)
		ft_remove_var_env(str);
	else if (ft_strncmp(str, "pwd", ft_strlen(str) - 1) == 0)
		ft_pwd(str);
	else if (ft_strncmp(str, "cd", 2) == 0)
		ft_cd(str);
}
