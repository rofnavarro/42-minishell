/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/10 20:55:29 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char *str, t_program *g_data)
{
	t_env	*tmp;
	char	*aux;

	if (ft_strncmp(str, "cd", ft_strlen(str) - 1) == 0)
	{
		tmp = g_data->env_start;
		while (ft_strncmp(tmp->env_line, "PWD=", 4) != 0)
			tmp = tmp->next;
		aux = ft_substr(tmp->env_line, 4, ft_strlen(tmp->env_line));
		tmp->next->env_line = ft_strjoin("OLDPWD=", aux);
		printf("%s\n", tmp->next->env_line);
		free(aux);
	}
}
