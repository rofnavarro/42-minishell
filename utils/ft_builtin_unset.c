/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:06:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/09 16:21:43 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_handler(char **str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		ft_remove_var_env(str[i]);
		ft_remove_var_export(str[i]);
	}
	g_data.exit_code = 0;
}