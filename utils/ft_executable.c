/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:28:08 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/01 02:05:20 by rinacio          ###   ########.fr       */
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

int	too_long_exit_arg(char *str)
{
	long long	nmbr;
	int			n;

	if (ft_strlen(str) > 20)
		return (0);
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (1);
	nmbr = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		n = *str - '0';
		if (nmbr > (9223372036854775807 - n) / 10)
			return (0);
		nmbr = nmbr * 10 + n;
		str++;
	}
	return (1);
}

void	ft_check_exit(t_token *token)
{
	if (token->cmd[1] && token->cmd[2])
	{
		ft_error(1, "exit: too many arguments");
		return ;
	}
	else if (token->cmd[1])
	{
		if (!ft_is_number(token->cmd[1]) || !too_long_exit_arg(token->cmd[1]))
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
	if (token->type == LESS_LESS || token->type == 8
		|| (token->prev && token->prev->type == LESS))
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
