/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:07:07 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/09 13:56:07 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_init(t_program *g_data)
{
    //g_data->cmd = ft_strdup("");
    //g_data->cmd_token =  ft_strdup("");
    // g_data->env =  NULL;
    // g_data->path =  NULL;
	g_data->token_start = NULL;
    g_data->status = 0;
    g_data->stop = 0;
}
