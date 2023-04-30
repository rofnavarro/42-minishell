/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:16:15 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/30 20:17:20 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_double_quotes(int *n, int *m, char *cmd, char **tmp)
{
	(*n)++;
	while (cmd[(*n)] != '\"')
	{
		if (cmd[(*n)] == '$')
		{
			if (cmd[(*n) + 1] == '?')
				ft_exit_code_handler(n, *tmp, m);
			else if (ft_strange_chars(cmd[(*n) + 1]) == 0)
			{
				(*tmp)[(*m)] = cmd[(*n)];
				(*m)++;
				(*n)++;
			}
			else if (cmd[(*n) + 1] == '{')
			{
				(*n)++;
				if (ft_var_handler(cmd, n, tmp, m, 2) == TRUE)
					return ;
				else
				{
					if (cmd[(*n)] == '}')
						(*n)++;
				}
			}
			else
				check_if_var(cmd, n, *tmp, m, 2);
		}
		else
		{
			(*tmp)[(*m)] = cmd[(*n)];
			(*m)++;
			(*n)++;
		}
	}
	(*n)++;
}

int	ft_no_quotes(int *n, int *m, char *cmd, char **tmp)
{
	if (cmd[(*n)] == '$')
	{
		if (cmd[(*n) + 1] == '?')
			ft_exit_code_handler(n, *tmp, m);
		else
		{
			if (cmd[(*n) + 1] == '{')
			{
				(*n)++;
				if (ft_var_handler(cmd, n, tmp, m, 0) == TRUE)
					return (1);
				else
				{
					if (cmd[(*n)] == '}')
						(*n)++;
				}
			}
			else if (ft_var_handler(cmd, n, tmp, m, 0) == TRUE)
				return (1);
		}
	}
	while (cmd[(*n)] != '\0')
	{
		(*tmp)[(*m)] = cmd[(*n)];
		(*m)++;
		(*n)++;
	}
	return (0);
}

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
			{
				if (ft_no_quotes(&n, &m, token->cmd[i], &tmp))
					break ;
			}
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
