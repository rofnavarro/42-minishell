/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:14:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/05 15:18:03 by rferrero         ###   ########.fr       */
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
	if (ft_strncmp(str[0], "env", ft_strlen(str[0])) == 0)
	{
		ft_print_env(str[0]);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "export", ft_strlen(str[0])) == 0 && \
			is_var_assigned(str[1]) == TRUE)
	{
		ft_add_var_env(str);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "unset", ft_strlen(str[0])) == 0)
	{
		ft_remove_var_env(str);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "pwd", ft_strlen(str[0])) == 0)
	{
		ft_pwd(str[0]);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "cd", ft_strlen(str[0])) == 0)
	{
		ft_cd(str);
		return (TRUE);
	}
	else if (ft_strncmp(str[0], "echo", ft_strlen(str[0])) == 0)
	{
		ft_echo(str);
		return (TRUE);
	}
	return (FALSE);
}
