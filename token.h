/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:22:22 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/04 19:24:47 by rinacio          ###   ########.fr       */
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
	SEMICOLON,
	EOC,
}	t_type;

//  structs
typedef struct s_token
{
	char			**cmd;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif