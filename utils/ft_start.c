/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:43:55 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/25 15:43:05 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_envp(char **envp)
{
	int		i;
	int		size;
	char	**ret;

	i = 0;
	size = 0;
	while (envp[i])
	{
		if (envp[i][ft_strlen(envp[i])] == '\0')
			size++;
		i++;
	}
	ret = (char **)malloc(sizeof(size));
	i = 0;
	while (envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		i++;
	}
	return (ret);
}

void	ft_start(char **envp, t_program *g_data)
{
	g_data->env = get_envp(envp);
}
