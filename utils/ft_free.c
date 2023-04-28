/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:01:41 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/28 16:52:33 by rinacio          ###   ########.fr       */
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

void	ft_free_matrix_int(int **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
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

void	ft_heredoc_close_exit(void)
{
	free(g_data.hd_delim);
	close(g_data.stdin_copy);
	close(g_data.stdout_copy);
	ft_free_loop();
	ft_free_data();
	rl_clear_history();
	free(g_data.pid);
	ft_free_matrix_int(g_data.fd, g_data.token_list_size - 1);
}
