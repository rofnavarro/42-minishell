/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:28:08 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/28 20:28:40 by rinacio          ###   ########.fr       */
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

int	ft_is_executable(t_token *token)
{
	if (ft_strncmp(token->cmd[0], "exit", 4) == 0
		&& ft_strlen(token->cmd[0]) == 4)
	{
		ft_exit();
		return (0);
	}
	if (token->type == LESS || token->type == LESS_LESS || token->type == 8)
		return (0);
	else if (token->prev && (token->prev->type == GREATER
			|| token->prev->type == GREATER_GREATER
			|| token->prev->type == 8))
		return (0);
	return (1);
}
