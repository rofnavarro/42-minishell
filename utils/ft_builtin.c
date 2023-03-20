/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:14:59 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/20 15:42:23 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_builtin(char *str, t_program *g_data)
{
	if (ft_strncmp(str, "env", ft_strlen(str) - 1) == 0)
		ft_print_env(str, g_data);
	// mudar o size para ft_strlen(token)
	else if (ft_strncmp(str, "export", 6) == 0)
		ft_add_var_env(str, g_data);
	// mudar o size para ft_strlen(token)
	else if (ft_strncmp(str, "unset", 5) == 0)
		ft_remove_var_env(str, g_data);
	else if (ft_strncmp(str, "pwd", ft_strlen(str) - 1) == 0)
		ft_pwd(str, g_data);
	else if (ft_strncmp(str, "cd", 2) == 0)
		ft_cd(str, g_data);
}
