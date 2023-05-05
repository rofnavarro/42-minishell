/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:50:00 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/04 20:51:30 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_code_handler(int *n, char *tmp, int *m)
{
	char	*tmp_var;

	tmp_var = ft_itoa(g_data.exit_code);
	tmp[*m] = '\0';
	ft_strlcat(tmp, tmp_var, (*m) + \
				ft_strlen(tmp_var) + 1);
	*m = ft_strlen(tmp);
	free(tmp_var);
	(*n) += 2;
}

int	ft_strange_chars(int c)
{
	if (c == '$' || c == '\'' || c == '\\' || c == '!' || c == '\"')
		return (0);
	else
		return (c);
}
