/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:22:22 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/26 22:53:28 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

//  enums
typedef enum e_token_type
{
	IDENTIFIER,
	STRING_LITERAL,
	INTEGER_LITERAL,
	MAYBE_DOUBLE,
	DOUBLE_LITERAL,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	L_PARENTHESIS,
	R_PARENTHESIS,
	L_BRACKET,
	R_BRACKET,
	L_CURLY,
	R_CURLY,
	PIPE,
	TWO_PIPES,
	COMMA,
	PERIOD,
	EQUAL,
	PLUS_PLUS,
	LESS_THAN,
	GREATER_THAN,
	LESS_EQUAL,
	GREATER_EQUAL,
	LEFT_ARROW,
	RIGHT_ARROW,
	PLUS_EQUAL,
	MINUS_EQUAL,
	EQUAL_EQUAL,
	NOT_EQUAL,
	SEMICOLOM
}	t_token_type;

//  structs
typedef struct s_tokens
{
	char				*data;
	t_token_type		type;
	size_t				line_number;
}	t_tokens;

#endif