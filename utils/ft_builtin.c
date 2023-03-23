/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:14:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/23 14:58:19 by rferrero         ###   ########.fr       */
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

void	is_builtin(char *str, t_program *g_data)
{
	if (ft_strncmp(str, "env", ft_strlen(str) - 1) == 0)
		ft_print_env(str, g_data);
	// mudar o size para ft_strlen(token)
	else if (ft_strncmp(str, "export", 6) == 0 && is_var_assigned(str) == TRUE)
		ft_add_var_env(str, g_data);
	// mudar o size para ft_strlen(token)
	else if (ft_strncmp(str, "unset", 5) == 0)
		ft_remove_var_env(str, g_data);
	else if (ft_strncmp(str, "pwd", ft_strlen(str) - 1) == 0)
		ft_pwd(str, g_data);
	else if (ft_strncmp(str, "cd", 2) == 0)
		ft_cd(str, g_data);
}
