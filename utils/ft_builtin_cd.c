/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:12:43 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/13 18:34:28 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*change_dir_down(char *str)
{
	int		size;
	char	*ret;

	size = ft_strlen(str);
	while (str[size - 1] != '\\')
		size--;
	ret = (char *)malloc(sizeof(size) + 1);
	ret[size + 1] = '\0';
	while (size >= 0)
		ret[size] = str[size];
	return (ret);
}

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
		// tmp->env_line = change_dir_down(tmp->env_line);
	}
}
