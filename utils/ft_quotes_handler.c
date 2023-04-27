/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:16:15 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/27 10:54:41 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_exit_code_handler(int *n, char *tmp, int *m)
{
	char	*tmp_var;

	tmp_var = ft_itoa(g_data.exit_code);
	tmp[*m] = '\0';
	ft_strlcat(tmp, tmp_var, (*m) + \
				ft_strlen(tmp_var) + 1);
	*m = ft_strlen(tmp);
	free(tmp_var);
	(*n) += 2;
}

static void	ft_check_empty_token(t_token *token, int *i)
{
	char	**new_cmd;
	int		lock_value;
	int		sup;

	if ((token->cmd[*i][0] == 10) && token->cmd[(*i) + 1] != NULL)
	{
		lock_value = 0;
		sup = 0;
		new_cmd = ft_env_calloc(ft_env_size(token->cmd) + 1);
		while (token->cmd[lock_value + sup])
		{
			if (lock_value + sup == *i)
				sup = 1;
			new_cmd[lock_value] = ft_strdup(token->cmd[lock_value + sup]);
			lock_value++;
		}
		ft_free_matrix(token->cmd);
		token->cmd = new_cmd;
		(*i)--;
	}
}

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
		if (str[*n] == '\'')
			break ;
		tmp_var[i++] = str[(*n)++];
	}
	tmp_var[i] = '\0';
	tmp_value = find_var_value(g_data.env, tmp_var);
	free(tmp_var);
	i = 0;
	if (tmp_value != NULL)
	{
		while (tmp_value[i] != '\0')
			tmp[(*m)++] = tmp_value[i++];
	}
	free(tmp_value);
}

static int	ft_var_handler(char *str, int *n, char **tmp, int *m)
{
	int		k;
	char	*tmp2;
	char	*tmp_var;

	k = 0;
	tmp_var = (char *)malloc(sizeof(char) * (ft_strlen(str) - (*n) + 1));
	tmp_var[ft_strlen(str) - (*n)] = '\0';
	(*n)++;
	while (str[(*n)] != '\0')
		tmp_var[k++] = str[(*n)++];
	tmp_var[k] = '\0';
	tmp2 = find_var_value(g_data.env, tmp_var);
	free(tmp_var);
	if (tmp2 == NULL)
	{
		*m = 1;
		free(*tmp);
		free(tmp2);
		*tmp = ft_strdup("\n");
		return (TRUE);
	}
	*tmp[*m] = '\0';
	ft_strlcat(*tmp, tmp2, (*m) + ft_strlen(tmp2) + 1);
	free(tmp2);
	*m = ft_strlen(*tmp);
	return (FALSE);
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
		tmp[m] = '\0';
		free(token->cmd[i]);
		token->cmd[i] = ft_strdup(tmp);
		free(tmp);
		ft_check_empty_token(token, &i);
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
