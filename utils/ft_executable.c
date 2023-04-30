/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:28:08 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/30 16:16:26 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_slash(char *str)
{
	char	**str_split;
	int		result;

	str_split = ft_split(str, '/');
	if (str_split[1])
		result = 1;
	else
		result = 0;
	ft_free_matrix(str_split);
	return (result);
}

int	ft_is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '-'
			&& arg[i] != '+' && arg[i] != '\"')
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_exit(t_token *token)
{
	if (token->cmd[1] && token->cmd[2])
	{
		ft_error(2, "exit: too many arguments");
		return ;
	}
	if (token->cmd[1])
	{
		if (!ft_is_number(token->cmd[1]) || (!ft_atoi_quotes(token->cmd[1])
			&& (ft_strncmp(token->cmd[1], "0", 1)
			|| ft_strlen(token->cmd[1]) != 1)))
				ft_error(2, "exit: numeric argument required");
		else
			g_data.exit_code = ft_atoi_quotes(token->cmd[1]) % 256;
	}
	ft_exit();
}

int	ft_is_executable(t_token *token)
{
	if (ft_strncmp(token->cmd[0], "exit", 4) == 0
		&& ft_strlen(token->cmd[0]) == 4)
	{
		printf("exit\n");
		ft_check_exit(token);
		return (0);
	}
	if (token->type == LESS || token->type == LESS_LESS || token->type == 8)
		return (0);
	else if (token->prev && (token->prev->type == GREATER
			|| token->prev->type == GREATER_GREATER
			|| token->prev->type == 8))
		return (0);
	else if (!ft_strncmp(token->cmd[0], "export", 6)
		&& ft_strlen(token->cmd[0]) == 6
		&& !token->cmd[1])
		return (1);
	else if (ft_is_builtin_parent(token->cmd[0])
		&& (token->type == PIPE || (token->prev
				&& token->prev->type == PIPE)))
		return (0);
	return (1);
}
