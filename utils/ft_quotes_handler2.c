/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_handler2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:35:38 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/30 20:17:31 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_single_quotes(int *n, int *m, char *cmd, char **tmp)
{
	(*n)++;
	while (cmd[(*n)] != '\'')
		(*tmp)[((*m)++)] = cmd[((*n)++)];
	(*n)++;
}

void	ft_check_empty_token(t_token *token, int *i)
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

void	check_if_var(char *str, int *n, char *tmp, int *m, int quote_type)
{
	char	*tmp_var;
	char	*tmp_value;
	int		i;

	(*n)++;
	tmp_var = (char *)malloc(sizeof(char) * (ft_strlen(str) - *n + 1));
	i = 0;
	while (str[(*n)] != '\"')
	{
		if (str[(*n)] == '\'' || str[(*n)] > 96 || str[(*n)] == ' ')
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

int	ft_var_handler(char *str, int *n, char **tmp, int *m, int quote_type)
{
	int		k;
	char	*tmp2;
	char	*tmp_var;

	k = 0;
	tmp_var = (char *)malloc(sizeof(char) * (ft_strlen(str) - (*n) + 1));
	tmp_var[ft_strlen(str) - (*n)] = '\0';
	while (str[++(*n)] != '\0')
	{
		if (str[(*n)] == '}')
			break ;
		if (str[(*n)] == '\"' && quote_type == 2)
			break ;
		tmp_var[k++] = str[(*n)];
	}
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
