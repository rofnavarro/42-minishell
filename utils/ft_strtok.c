/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:34:08 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/17 15:33:46 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_delim(char c, const char *delim, t_program *g_data)
{
	int	i;

	i = 0;
	if (c == ' ')
		return (TRUE);
	while (delim[i] != '\0')
	{
		if (c == delim[i])
		{
			if (g_data->cmd_type == 5)
				g_data->cmd_type = i;
			else if ((g_data->cmd_type == 1 && c == '<') || \
					(g_data->cmd_type == 3 && c == '>'))
				g_data->cmd_type++;
			else
				ft_error("Error: unknown operator\n", 1);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*ft_strtok(char *str, const char *delim, t_program *g_data)
{
	static char	*backup_string;
	char		*ret;
	int			i;

	i = 0;
	g_data->cmd_type = 5;
	if (!str)
		str = backup_string;
	if (!str || *str == '\0')
		return (NULL);
	while (*str == ' ')
		str++;
	ret = str;
	while (!is_delim(*str, delim, g_data) && *str)
		str++;
	if (*str == '\0')
		backup_string = str;
	else
	{
		*str++ = '\0';
		while (is_delim(*str, delim, g_data) && *str != '\0')
			str++;
		backup_string = str;
	}
	return (ret);
}
