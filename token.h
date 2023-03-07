/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:22:22 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/07 17:45:07 by rferrero         ###   ########.fr       */
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
	EOC,
}	t_type;

//  structs
typedef struct s_token
{
	char			*cmd;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif