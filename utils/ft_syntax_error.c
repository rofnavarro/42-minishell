/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:39:17 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/24 03:07:51 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_char_error(t_type type)
{
    switch(type)
    {
        case PIPE:
            return ("`|'");
        case GREATER:
            return ("`>'");
        case GREATER_GREATER:
            return ("`>>'");
        case LESS:
            return ("`<'");
        case LESS_LESS:
            return ("`<<'");
        default:
            return ("`newline'");
    }
}

int ft_check_sintax(void)
{
	t_token *aux;
    char    *token_error;

	if (!g_data.token_start)
		return (1);
	aux = g_data.token_start;
	while (aux)
	{
        if (aux->type == PIPE && !aux->cmd[0])
        {
            token_error = ft_strjoin("syntax error near unexpected token ", "`|'");
            ft_error(2, token_error);
            free(token_error);
            return (1);
        }
        else if ((aux->type == GREATER || aux->type == GREATER_GREATER
                || aux->type == LESS || aux->type == LESS_LESS))
        {
            if (!aux->next)
                token_error = ft_strjoin("syntax error near unexpected token ", "`newline'");
            else if (!aux->next->cmd[0])
                token_error = ft_strjoin("syntax error near unexpected token ", ft_char_error(aux->next->type));
            ft_error(2, token_error);
            free(token_error);
            return (1);
        }
        aux = aux->next;
	}
    return (0);
}
