/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 04:14:15 by rinacio           #+#    #+#             */
/*   Updated: 2023/05/12 00:47:40 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_check_args_after_redirection(t_token *token)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	while (token->next->cmd[i])
		i++;
	new_cmd = ft_get_tmp(token, &j, i);
	i = 1;
	while (token->next->cmd[i])
	{
		new_cmd[j] = ft_strdup(token->next->cmd[i]);
		j++;
		i++;
	}
	new_cmd[j] = NULL;
	ft_free_matrix(token->cmd);
	return (new_cmd);
}

char	**ft_get_tmp(t_token *token, int *j, int i)
{
	char	**tmp;
	char	**new_cmd;

	*j = 0;
	while (token->cmd[(*j)])
		(*j)++;
	tmp = (char **)malloc(sizeof(char *) * (*j + 1));
	*j = 0;
	while (token-> cmd[(*j)])
	{
		tmp[(*j)] = ft_strdup(token->cmd[(*j)]);
		(*j)++;
	}
	tmp[(*j)] = NULL;
	new_cmd = (char **)malloc(sizeof(char *) * (*j + i));
	*j = 0;
	while (tmp[(*j)])
	{
		new_cmd[(*j)] = ft_strdup(tmp[(*j)]);
		(*j)++;
	}
	ft_free_matrix(tmp);
	return (new_cmd);
}

char	**ft_new_cmd(t_token *token)
{
	int		i;
	char	**new_cmd;

	free(token->cmd);
	token->cmd = (char **)malloc(sizeof(char *) * 2);
	token->cmd[0] = ft_strdup(token->next->cmd[0]);
	token->cmd[1] = NULL;
	i = 0;
	while (token->next->cmd[i])
		i++;
	new_cmd = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	free(token->next->cmd[0]);
	while (token->next->cmd[i + 1])
	{
		new_cmd[i] = ft_strdup(token->next->cmd[i + 1]);
		free(token->next->cmd[i + 1]);
		i++;
	}
	new_cmd[i] = NULL;
	free(token->next->cmd[i + 1]);
	free(token->next->cmd);
	return (new_cmd);
}

int	ft_is_export_wo_arg(t_token *token)
{
	if ((ft_strncmp(token->cmd[0], "export", ft_strlen(token->cmd[0])) == 0
			&& ft_strlen(token->cmd[0]) == ft_strlen("export"))
		&& !token->cmd[1])
		return (1);
	return (0);
}

t_token	*ft_next_pipe(t_token *token)
{
	t_token	*aux;

	if (token->next)
		aux = token->next;
	else
		return (NULL);
	while (aux)
	{
		if (aux->type == LESS || aux->type == LESS_LESS
			|| aux->type == GREATER || aux->type == LESS)
				aux = aux->next;
		else if (aux->type == PIPE)
			return (aux->next);
		else
			return (NULL);
	}
	return (NULL);
}
