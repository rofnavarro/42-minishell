/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:16:15 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/27 00:47:29 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_if_var(char *str, int *n, char *tmp, int *m)
{
	char	*tmp_var;
	char	*tmp_value;
	int		i;

	(*n)++;
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
	char	**new_cmd;
	int		i;
	int		n;
	int		m;
	int		k;
	int		lock_value;
	int		sup;

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
						else
							check_if_var(token->cmd[i], &n, tmp, &m);
					}
					// if (token->cmd[i][n] == '\'')
					// {
					// 	tmp[m] = '\'';
					// 	tmp_var = ft_strtrim(token->cmd[i], '\'');
					// 	m++;
					// 	tmp[m] = '\0';
					// 	ft_strlcat(tmp, tmp_var, m + \
					// 					ft_strlen(tmp_var) + 1);
					// 	m = ft_strlen(tmp);
					// 	free(tmp_var);
					// 	tmp = (char *)malloc(sizeof(char) * ft_strlen())
					// }
					else
					{
						tmp[m] = token->cmd[i][n];
						m++;
						n++;
					}
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
							tmp2 = find_var_value(g_data.env, tmp_var);
							free(tmp_var);
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
						}
					}
					else if (token->cmd[i][n] != '\0')
					{
						tmp[m] = token->cmd[i][n];
						m++;
						n++;
					}
				}
			}
			tmp[m] = '\0';
		}
		tmp[m] = '\0';
		free(token->cmd[i]);
		token->cmd[i] = ft_strdup(tmp);
		free(tmp);
		if ((token->cmd[i][0] == 10) && token->cmd[i + 1] != NULL)
		{
			lock_value = 0;
			sup = 0;
			new_cmd = ft_env_calloc(ft_env_size(token->cmd) + 1);
			while (token->cmd[lock_value + sup])
			{
				if (lock_value  + sup == i)
					sup = 1;
				new_cmd[lock_value] = ft_strdup(token->cmd[lock_value + sup]);
				lock_value++;
			}
			ft_free_matrix(token->cmd);
			token->cmd = new_cmd;
			i--;
		}
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
