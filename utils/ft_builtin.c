/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:14:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/30 05:51:28 by rinacio          ###   ########.fr       */
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

int	ft_is_builtin_parent(char *input)
{
	if ((ft_strncmp(input, "export", ft_strlen(input)) == 0 && \
		ft_strlen(input) == ft_strlen("export")) || \
		ft_strncmp(input, "unset", ft_strlen(input)) == 0 && \
		ft_strlen(input) == ft_strlen("unset") || \
		ft_strncmp(input, "cd", ft_strlen(input)) == 0 && \
		ft_strlen(input) == ft_strlen("cd"))
		return (TRUE);
	return (FALSE);
}

int	ft_is_builtin_child(char *input)
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
		if (ft_strncmp(str[0], "export", ft_strlen(str[0])) == 0)
		{
			if (str[1] && is_var_assigned(str[1]) == TRUE)
			{
				ft_add_var_env(str);
				get_export(g_data.env);
			}
			else if (str[1] == NULL || is_var_assigned(str[1]) == FALSE)
				ft_export(str);
		}
		else if (ft_strncmp(str[0], "unset", ft_strlen(str[0])) == 0)
		{
			ft_remove_var_env(str);
			get_export(g_data.env);
		}
		else if (ft_strncmp(str[0], "cd", ft_strlen(str[0])) == 0)
			ft_cd(str);
		return (TRUE);
	}
	return (FALSE);
}
