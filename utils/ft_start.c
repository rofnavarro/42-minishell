/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:43:55 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/28 15:56:44 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_path(char **envp)
{
	char	**ret;
	char	*tmp;
	int		i;

	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	tmp = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	printf("%s\n", tmp);
}

static char	**get_envp(char **envp)
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
	g_data->path = get_path(envp);
}
