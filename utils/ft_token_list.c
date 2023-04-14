/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:53:47 by rinacio           #+#    #+#             */
/*   Updated: 2023/04/14 20:31:53 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_token(char *cmd_token, t_type cmd_type)
{
	t_token	*new_token;
	t_token	*aux;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->cmd = ft_split(cmd_token, ' ');
	new_token->cmd = ft_token_quotes(new_token->cmd);
	new_token->type = cmd_type;
	new_token->prev = NULL;
	new_token->next = NULL;
	if (!g_data.token_start)
		g_data.token_start = new_token;
	else
	{
		aux = g_data.token_start;
		while (aux->next)
			aux = aux->next;
		aux->next = new_token;
		new_token->prev = aux;
		new_token->next = NULL;
	}
}

char	**ft_token_quotes(char **cmd)
{
	char	*temp;
	int		i;

	i = 0;
	while (cmd[i])
	{
		temp = ft_strtrim(ft_switch_inside_quotation(cmd[i]), "\"");
		free(cmd[i]);
		cmd[i] = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (cmd);
}

void	ft_print_token_list(void)
{
	t_token	*aux;
	int		i;

	if (!g_data.token_start)
		return ;
	aux = g_data.token_start;
	while (aux)
	{
		i = 0;
		while (aux->cmd[i])
		{
			printf("cmd[%d]: ", i);
			printf("%s\n", aux->cmd[i]);
			i++;
		}
		printf("separator: %d\n", (int)aux->type);
		printf("\n");
		aux = aux->next;
	}
}

void	ft_free_token_list(t_token *token, int start)
{
	if (!token)
		return ;
	if (token->next)
		ft_free_token_list(token->next, 0);
	else if (token->prev)
		token->prev->next = NULL;
	token->prev = NULL;
	token->next = NULL;
	if (start == 1)
		g_data.token_start = NULL;
	ft_free_matrix(token->cmd);
	free(token);
}
