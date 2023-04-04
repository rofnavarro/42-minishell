/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:14:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/04 17:30:18 by rferrero         ###   ########.fr       */
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

int	is_builtin(char **str)
{
	if (ft_strncmp(str[0], "env", ft_strlen(str[0]) - 1) == 0)
	{
		ft_print_env(str[0]);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "export", 6) == 0 && is_var_assigned(str[1]) == TRUE)
	{
		ft_add_var_env(str);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "unset", 5) == 0)
	{
		ft_remove_var_env(str);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "pwd", ft_strlen(str[0]) - 1) == 0)
	{
		ft_pwd(str[0]);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "cd", 2) == 0)
	{
		ft_cd(str[0]);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "echo", 4) == 0)
	{
		ft_echo(str);
		return (TRUE);
	}
	return (FALSE);
}
