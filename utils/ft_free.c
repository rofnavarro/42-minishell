/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:01:41 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/18 19:05:18 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i] != NULL)
		free(matrix[i]);
	free(matrix);
}

void	ft_free_data(void)
{
	if (g_data.env != NULL)
		ft_free_matrix(g_data.env);
	if (g_data.path != NULL)
		ft_free_matrix(g_data.path);
	if (g_data.export != NULL)
		ft_free_matrix(g_data.export);
}

void	ft_free_loop(void)
{
	ft_free_token_list(g_data.token_start, 1);
	free(g_data.cmd);
	free(g_data.user);
}
