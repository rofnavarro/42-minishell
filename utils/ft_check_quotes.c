/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:02:23 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/05 14:38:50 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quotes(char *arg)
{
	int	count_single;
	int	count_double;
	int	i;

	i = 0;
	count_single = 0;
	count_double = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
			count_double++;
		else if (arg[i] == '\'')
			count_single++;
		i++;
	}
	if (count_single % 2 || count_double % 2)
		return (1);
	return (0);
}

char	ft_substitute_char(char c)
{
	char	*characters;
	int		i;

	characters = " |<>;";
	if (c < 6)
		return (characters[c - 1]);
	else
	{
		i = 0;
		while (characters[i] != c)
			i++;
		return (i + 1);
	}
}

char	*ft_switch_inside_quotation(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
			{
				if (str[i] == ' ' || str[i] == '|' || str[i] == '<' || \
					str[i] == '>' || str[i] == ';' || str[i] < 6)
					str[i] = ft_substitute_char(str[i]);
				i++;
			}
		}
		i++;
	}
	return (str);
}
