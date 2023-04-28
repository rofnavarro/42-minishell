/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:11:31 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/19 15:03:58 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_test_path(int i, t_token *token)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(g_data.path[i], "/");
	path = ft_strjoin(temp, token->cmd[0]);
	free(temp);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*ft_get_cmd_path(t_token *token)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	get_path();
	if (g_data.path == NULL)
	{
		printf("command not found: %s\n", token->cmd[0]);
		return (NULL);
	}
	while (g_data.path[i])
	{
		cmd_path = ft_test_path(i, token);
		if (cmd_path)
			break ;
		i++;
	}
	if (cmd_path == NULL)
		ft_cmd_not_found(token->cmd[0]);
	return (cmd_path);
}

void	ft_cmd_not_found(char *cmd)
{
	if (ft_strncmp(cmd, "$?", ft_strlen(cmd)) == 0 && \
		ft_strlen(cmd) == 2)
		printf("%d: command not found\n", g_data.exit_code);
	else
		printf("%s: command not found\n", cmd);
	g_data.exit_code = 127;
}
