/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:20:25 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/10 21:23:55 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char *str, t_program *g_data)
{
	t_env	*tmp;
	char	*aux;

	if (ft_strncmp(str, "pwd", ft_strlen(str) - 1) == 0)
	{
		tmp = g_data->env_start;
		while (ft_strncmp(tmp->env_line, "PWD=", 4) != 0)
			tmp = tmp->next;
		aux = ft_substr(tmp->env_line, 4, ft_strlen(tmp->env_line));
		printf("%s\n", aux);
		free(aux);
	}
}
