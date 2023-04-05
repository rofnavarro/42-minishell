/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:34:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/05 16:48:21 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_delim(char c, const char *delim)
{
	int	i;

	i = 0;new_token->
	while (delim[i] != '\0')
	{
		if (c == delim[i])
		{
			if (g_data.cmd_type == 6)
				g_data.cmd_type = i;
			else if ((g_data.cmd_type == 1 && c == '<') || \
					(g_data.cmd_type == 3 && c == '>'))
				g_data.cmd_type++;
			else
			{
				ft_error(ENOENT);
				return (FALSE);
			}
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*backup_string;
	char		*ret;
	int			i;

	i = 0;
	g_data.cmd_type = 6;
	if (!str)
		str = backup_string;
	if (!str || *str == '\0')
		return (NULL);
	while (*str == ' ')
		str++;
	ret = str;
	while (!is_delim(*str, delim) && *str)
		str++;
	if (*str == '\0')
		backup_string = str;
	else
	{
		*str++ = '\0';
		while (is_delim(*str, delim) && *str != '\0')
			str++;
		backup_string = str;
	}
	return (ret);
}
