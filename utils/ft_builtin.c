/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:14:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/12 01:57:03 by coder            ###   ########.fr       */
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

static int	ft_is_builtin_parent(char *input)
{
	if (ft_strncmp(input, "export", ft_strlen(input)) == 0 || \
		ft_strncmp(input, "unset", ft_strlen(input)) == 0 || \
		ft_strncmp(input, "cd", ft_strlen(input)) == 0)
		return (TRUE);
	return (FALSE);
}

static int	ft_builtin_child(char *input)
{
	if (ft_strncmp(input, "env", ft_strlen(input)) == 0 || \
		ft_strncmp(input, "pwd", ft_strlen(input)) == 0 || \
		ft_strncmp(input, "echo", ft_strlen(input)) == 0)
		return (TRUE);
	return (FALSE);
}

int	is_builtin(char **str)
{
	if (ft_is_builtin_parent(str[0]) == TRUE)
	{
		if (ft_strncmp(str[0], "export", ft_strlen(str[0])) == 0 && \
				is_var_assigned(str[1]) == TRUE)
			ft_add_var_env(str);
		else if (ft_strncmp(str[0], "unset", ft_strlen(str[0])) == 0)
			ft_remove_var_env(str);
		else if (ft_strncmp(str[0], "cd", ft_strlen(str[0])) == 0)
			ft_cd(str);
		return (TRUE);
	}
	if (ft_is_builtin_child(str[0]) == TRUE)
	{
		if (ft_strncmp(str[0], "env", ft_strlen(str[0])) == 0 && str[1] == NULL)
			ft_print_env(str[0]);
		else if (ft_strncmp(str[0], "pwd", ft_strlen(str[0])) == 0 && \
					str[1] == NULL)
			ft_pwd(str[0]);
		else if (ft_strncmp(str[0], "echo", ft_strlen(str[0])) == 0)
			ft_echo(str);
		return (TRUE);
	}
	return (FALSE);
}
