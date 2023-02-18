# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 13:12:03 by rferrero          #+#    #+#              #
#    Updated: 2023/02/18 13:46:50 by rferrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						=			minishell

CC							=			cc
CCFLAGS						=			-Wall -Wextra -Werror

AR							=			ar
ARFLAGS						=			rcs

RM							=			rm -rf

SRC							=			minishell.c \
										$(addprefix utils/, )

OBJ							=			$(SRC:.c=.o)

.c.o:
							$(CC) $(CCFLAGS) -c $< -o $(<:.c=.o)

all:						$(NAME)

$(NAME):					$(OBJ)
							$(AR) $(ARFLAGS) $(NAME) $(OBJ)

clean:
							$(RM) $(OBJ)

fclean:						clean
							$(RM) $(NAME)

re:							fclean all

.PHONY:						all clean fclean re