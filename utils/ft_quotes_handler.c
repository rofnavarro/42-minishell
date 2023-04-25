/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:16:15 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/25 15:25:12 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_if_var(char *str, int *n, char *tmp, int *m)
{
	char 	*tmp_var;
	char	*tmp_value;
	int		i;

	tmp_var = (char *)malloc(sizeof(char) * (ft_strlen(str) - *n + 1));
	i = 0;
	while (str[*n] != '\"')
	{
		tmp_var[i] = str[*n];
		i++;
		(*n)++;
	}
	tmp_var[i] = '\0';
	tmp_value = find_var_value(g_data.env, tmp_var);
	free(tmp_var);
	i = 0;
	if (tmp_value != NULL)
	{
		while (tmp_value[i] != '\0')
		{
			tmp[(*m)] = tmp_value[i];
			(*m)++;
			i++;
		}
	}
	free(tmp_value);
}
static void	exit_code_handler(char *str, int *n, char *tmp, int *m)
{
	char	*tmp_code;
	int		i;

	tmp_code = ft_itoa(g_data.exit_code);
	printf("%s\n", tmp_code);
	i = 0;
	while (tmp_code[i] != '\0')
	{
		tmp[*m] = tmp_code[i];
		(*m)++;
		i++;
	}
	free(tmp_code);
	(*n)++;
}

static void	quotes_replace(t_token *token)
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
				{
					tmp[m] = token->cmd[i][n];
					n++;
					m++;
				}
			}
			else if (token->cmd[i][n] == '\"')
			{
				n++;
				while (token->cmd[i][n] != '\"')
				{
					if (token->cmd[i][n] == '$')
					{
						n++;
						if (token->cmd[i][n] == '?')
							exit_code_handler(token->cmd[i], &n, tmp, &m);
							if (token->cmd[i][n] != '\"')
						check_if_var(token->cmd[i], &n, tmp, &m);
					}
					else
					{
						tmp[m] = token->cmd[i][n];
						n++;
						m++;
					}
				}
			}
			else
			{
				tmp[m] = token->cmd[i][n];
				m++;
			}
			n++;
		}
		tmp[m] = '\0';
		free(token->cmd[i]);
		token->cmd[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
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
}
