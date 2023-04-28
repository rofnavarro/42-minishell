/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:16:15 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/28 19:43:24 by rferrero         ###   ########.fr       */
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
			{
				n++;
				while (token->cmd[i][n] != '\'')
					tmp[m++] = token->cmd[i][n++];
				break ;
			}
			else if (token->cmd[i][n] == '\"')
			{
				n++;
				while (token->cmd[i][n] != '\"')
				{
					if (token->cmd[i][n] == '$')
					{
						if (token->cmd[i][n + 1] == '?')
							ft_exit_code_handler(&n, tmp, &m);
						else
							check_if_var(token->cmd[i], &n, tmp, &m);
					}
					else
						tmp[m++] = token->cmd[i][n++];
				}
				tmp[m] = '\0';
				n++;
			}
			else
			{
				while (token->cmd[i][n] != '\0')
				{
					if (token->cmd[i][n] == '$')
					{
						if (token->cmd[i][n + 1] == '?')
							ft_exit_code_handler(&n, tmp, &m);
						else
						{
							if (ft_var_handler(token->cmd[i], &n, &tmp, &m) == TRUE)
								break ;
						}
					}
					else if (token->cmd[i][n] != '\0')
						tmp[m++] = token->cmd[i][n++];
				}
			}
			tmp[m] = '\0';
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
