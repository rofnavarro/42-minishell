/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:16:15 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/26 23:35:52 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_if_var(char *str, int *n, char *tmp, int *m)
{
	char	*tmp_var;
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

static void	quotes_replace(t_token *token)
{
	char	*tmp_var;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		n;
	int		m;
	int		k;

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
					m++;
					n++;
				}
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
						{
							tmp_var = ft_itoa(g_data.exit_code);
							tmp[m] = '\0';
							ft_strlcat(tmp, tmp_var, m + \
										ft_strlen(tmp_var) + 1);
							m = ft_strlen(tmp);
							free(tmp_var);
							n += 2;
						}
						else if (token->cmd[i][n] != '\0')
						{
							n++;
							check_if_var(token->cmd[i], &n, tmp, &m);
						}
					}
					else
					{
						tmp[m] = token->cmd[i][n];
						m++;
						n++;
					}
				}
				break ;
			}
			else
			{
				while (token->cmd[i][n] != '\0')
				{
					if (token->cmd[i][n] == '$')
					{
						if (token->cmd[i][n + 1] == '?')
						{
							tmp_var = ft_itoa(g_data.exit_code);
							tmp[m] = '\0';
							ft_strlcat(tmp, tmp_var, m + \
										ft_strlen(tmp_var) + 1);
							m = ft_strlen(tmp);
							free(tmp_var);
							n += 2;
						}
						else
						{
							k = 0;
							tmp_var = (char *)malloc(sizeof(char) * (ft_strlen(token->cmd[i]) - n + 1));
							tmp_var[ft_strlen(token->cmd[i]) - n] = '\0';
							n++;
							while (token->cmd[i][n] != '\0')
							{
								tmp_var[k] = token->cmd[i][n];
								n++;
								k++;
							}
							tmp_var[k] = '\0';
							// printf("\n\n%s\n\n", tmp_var);
							tmp2 = find_var_value(g_data.env, tmp_var);
							free(tmp_var);
							// printf("\n\n%s\n\n", tmp2);
							if (tmp2 == NULL)
							{
								m = 1;
								free(tmp);
								free(tmp2);
								tmp = ft_strdup("\n");
								break ;
							}
							tmp[m] = '\0';
							ft_strlcat(tmp, tmp2, m + ft_strlen(tmp2) + 1);
							free(tmp2);
							m = ft_strlen(tmp);
							break ;
						}
					}
					else if (token->cmd[i][n] != '\0')
					{
						tmp[m] = token->cmd[i][n];
						m++;
						n++;
					}
					break ;
				}
			}
			tmp[m] = '\0';
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
	free (aux);
}
