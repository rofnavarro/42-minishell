/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 02:39:36 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/15 03:20:10 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint_empty(int sig)
{
	free(g_data.user);
	g_data.user = find_var_value(g_data.env, "USER");
	printf("\n%s:$ ", g_data.user);
}
