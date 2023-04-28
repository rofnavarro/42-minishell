/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:39:17 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/28 17:48:28 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_char_error(t_type type)
{
	if (type == PIPE)
		return ("`|'");
	else if (type == GREATER)
		return ("`>'");
	else if (type == GREATER_GREATER)
		return ("`>>'");
	else if (type == LESS)
		return ("`<'");
	else if (type == LESS_LESS)
		return ("`<<'");
	else
		return ("`newline'");
}

char	*ft_syntax_error(t_token *aux)
{
	char	*token_error;

	if (aux->type == PIPE && !aux->cmd[0])
	{
		token_error = ft_strjoin(
				"syntax error near unexpected token ", "`|'");
		return (token_error);
	}
	else if ((aux->type == GREATER || aux->type == GREATER_GREATER
			|| aux->type == LESS || aux->type == LESS_LESS))
	{
		if (!aux->next)
			token_error = ft_strjoin(
					"syntax error near unexpected token ", "`newline'");
		else if (!aux->next->cmd[0])
			token_error = ft_strjoin(
					"syntax error near unexpected token ",
					ft_char_error(aux->next->type));
		else
			return (0);
		return (token_error);
	}
	else
		return (NULL);
}

int	ft_check_sintax(void)
{
	t_token	*aux;
	char	*syntax_error;

	if (!g_data.token_start)
		return (1);
	aux = g_data.token_start;
	while (aux)
	{
		syntax_error = ft_syntax_error(aux);
		if (syntax_error)
		{
			ft_error(2, syntax_error);
			free(syntax_error);
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}
