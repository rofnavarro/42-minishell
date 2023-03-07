/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:34:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/06 16:31:26 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_str = NULL;
	int			index;
	int			str_len;
	int			found;

	index = 0;
	found = 0;
	if (delim == 0 || (str == 0 && last_str == 0))
		return (0);
	if (str == 0)
		str = last_str;
	str_len = ft_strlen(str);
	while (index < str_len)
	{
		if (str[index] == delim[0])
		{
			found = 1;
			break ;
		}
		index++;
	}
	if (!found)
	{
		last_str = 0;
		return (str);
	}
	if (str[0] == delim[0])
	{
		last_str = (str + 1);
		return ((char *)delim);
	}
	str[index] = '\0';
	if ((str + index + 1) != 0)
		last_str = (str + index + 1);
	else
		last_str = 0;
	return (str);
}
