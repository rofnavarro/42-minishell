/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:22:22 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/06 16:30:04 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

//  enums
typedef enum e_type
{
	PIPE,
	LESS,
	LESS_LESS,
	GREATER,
	GREATER_GREATER,
}	t_type;

//  structs
typedef struct s_token
{
	char			*cmd;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	char		*str;
	t_token		type;
	size_t		line_number;
}	t_lexer;


#endif