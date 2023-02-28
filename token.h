/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:22:22 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/28 11:36:07 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

//  enums
typedef enum e_token
{
	PIPE,
	LESS,
	LESS_LESS,
	GREATER,
	GREATER_GREATER,
}	t_token;

//  structs
typedef struct s_lexer
{
	char		*str;
	t_token		type;
	size_t		line_number;
}	t_lexer;

#endif