/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:49:11 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/05 18:42:52 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_double_quotes(int *n, int *m, char *cmd, char **tmp)
{
	(*n)++;
	while (cmd[(*n)] != '\"')
	{
		if (cmd[(*n)] == '$' && ft_strlen(cmd) > 3)
			ft_handle_dolar_on_double(cmd, n, tmp, m);
		else
		{
			(*tmp)[(*m)] = cmd[(*n)];
			(*m)++;
			(*n)++;
		}
	}
	(*n)++;
}

void	ft_handle_dolar_on_double(char *str, int *n, char **tmp, int *m)
{
	if (str[(*n) + 1] == '?')
		ft_exit_code_handler(n, *tmp, m);
	else if (ft_strange_chars(str[(*n) + 1]) == 0)
	{
		(*tmp)[(*m)] = str[(*n)];
		(*m)++;
		(*n)++;
	}
	else if (str[(*n) + 1] == '{')
	{
		(*n)++;
		check_if_var(str, n, *tmp, m);
		if (str[(*n)] == '}')
			(*n)++;
	}
	else
		check_if_var(str, n, *tmp, m);
}

void	ft_no_quotes(int *n, int *m, char *cmd, char **tmp)
{
	while (cmd[(*n)] != '\0')
	{
		if (cmd[(*n)] == '$' && ft_strlen(cmd) > 1)
			ft_handle_dolar_no_quotes(cmd, n, tmp, m);
		else if (cmd[(*n)] == '\'' || cmd[(*n)] == '\"')
			(*n)++;
		else
		{
			(*tmp)[(*m)] = cmd[(*n)];
			(*m)++;
			(*n)++;
		}
	}
}

void	ft_handle_dolar_no_quotes(char *str, int *n, char **tmp, int *m)
{
	if (str[(*n) + 1] == '?')
		ft_exit_code_handler(n, *tmp, m);
	else
	{
		if (str[(*n) + 1] == '{')
		{
			(*n)++;
			check_if_var(str, n, *tmp, m);
			if (str[(*n)] == '}')
				(*n)++;
		}
		else
			check_if_var(str, n, *tmp, m);
	}
}
