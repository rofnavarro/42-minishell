/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:53:47 by rinacio           #+#    #+#             */
/*   Updated: 2023/03/09 19:44:44 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_token(t_program *g_data, char *cmd_token, t_type cmd_type)
{
	t_token	*new_token;
	t_token	*aux;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->cmd = cmd_token;
	new_token->type = cmd_type;
	new_token->prev = NULL;
	new_token->next = NULL;
	if (!g_data->token_start)
		g_data->token_start = new_token;
	else
	{
		aux = g_data->token_start;
		while (aux->next)
			aux = aux->next;
		aux->next = new_token;
		new_token->prev = aux;
		new_token->next = NULL;
	}
}

void	ft_print_token_list(t_program *g_data)
{
	t_token	*aux;

	if (!g_data->token_start)
		return ;
	aux = g_data->token_start;
	while (aux)
	{
		printf("%s\n", aux->cmd);
		aux = aux->next;
	}
}

void	ft_free_token_list(t_program *g_data, t_token *token, int start)
{
	if (!token)
		return ;
	if (token->next)
		ft_free_token_list(g_data, token->next, 0);
	else if (token->prev)
		token->prev->next = NULL;
	token->prev = NULL;
	token->next = NULL;
	if (start == 1)
		g_data->token_start = NULL;
	free(token);
}
