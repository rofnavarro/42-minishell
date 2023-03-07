/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:34:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/07 14:37:25 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_delim(char c, const char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (TRUE);
		delim++;
	}
	return (FALSE);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*backup_string;
	char		*ret;

	if (!str)
		str = backup_string;
	if (!str)
		return (NULL);
	while (TRUE)
	{
		if (is_delim(*str, delim))
		{
			str++;
			continue ;
		}
		if (*str == '\0')
			return (NULL);
		break ;
	}
	ret = str;
	while (TRUE)
	{
		if (*str == '\0')
		{
			backup_string = str;
			return (ret);
		}
		if (is_delim(*str, delim))
		{
			*str = '\0';
			backup_string = str + 1;
			return (ret);
		}
		str++;
	}
}
