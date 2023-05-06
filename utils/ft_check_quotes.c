/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:02:23 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/04 20:50:25 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quotes(char *arg)
{
	int		count;
	char	quote;
	int		i;

	i = 0;
	quote = '\0';
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
		{
			if (quote == '\0')
			{
				quote = arg[i];
				count++;
			}
			else if (arg[i] == quote)
				count++;
		}
		i++;
	}
	if (count % 2)
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

void	ft_handle_inclosed_quotes(void)
{
	char	*read;

	read = readline("> ");
	g_data.cmd = ft_strjoin_free(g_data.cmd, read);
	free(read);
}
