/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:16:15 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/04 20:59:27 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quotes_replace(t_token *token)
{
	char	*tmp;
	int		i;
	int		n;
	int		m;

	i = 0;
	while (token->cmd[i])
	{
		tmp = (char *)malloc(sizeof(char) * ft_strlen(token->cmd[i]) + 1000);
		n = 0;
		m = 0;
		while (token->cmd[i][n])
		{
			if (token->cmd[i][n] == '\'')
				ft_single_quotes(&n, &m, token->cmd[i], &tmp);
			else if (token->cmd[i][n] == '\"')
				ft_double_quotes(&n, &m, token->cmd[i], &tmp);
			else
				ft_no_quotes(&n, &m, token->cmd[i], &tmp);
		}
		finishe_quote_replace(token, &i, &tmp, &m);
	}
}

void	finishe_quote_replace(t_token *token, int *i, char **tmp, int *m)
{
	(*tmp)[(*m)] = '\0';
	free(token->cmd[(*i)]);
	token->cmd[(*i)] = ft_strdup((*tmp));
	free((*tmp));
	ft_check_empty_token(token, i);
	(*i)++;
}

void	ft_quotes_handler(void)
{
	t_token	*aux;

	aux = g_data.token_start;
	while (aux)
	{
		quotes_replace(aux);
		aux = aux->next;
	}
	free (aux);
}
