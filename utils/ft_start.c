/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:43:55 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/13 18:19:33 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_path(t_program *g_data, char **envp)
{
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	g_data->path = (ft_split(envp[i] + 5, ':'));
}

static void	add_env_line(t_program *g_data, char *envp)
{
	t_env	*new_env_line;
	t_env	*tmp;

	new_env_line = (t_env *)malloc(sizeof(t_env));
	new_env_line->env_line = envp;
	new_env_line->next = NULL;
	if (!g_data->env_start)
		g_data->env_start = new_env_line;
	else
	{
		tmp = g_data->env_start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_env_line;
		new_env_line->next = NULL;
	}
}

static void	get_env(t_program *g_data, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		add_env_line(g_data, envp[i]);
}

void	ft_start(char **envp, t_program *g_data)
{
	g_data->env_start = NULL;
	g_data->path = NULL;
	get_path(g_data, envp);
	get_env(g_data, envp);
}

void	print_env(t_program *g_data)
{
	t_env	*tmp;
	tmp = g_data->env_start;
	while (tmp->next != NULL)
	{
		printf("%s\n", tmp->env_line);
		tmp = tmp->next;
	}
}