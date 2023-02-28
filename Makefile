# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 13:12:03 by rferrero          #+#    #+#              #
#    Updated: 2023/02/28 20:45:53 by rferrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						=			minishell

CC							=			cc
CCFLAGS						=			-Wall -Wextra -Werror

RL							=			-l readline

RM							=			rm -rf

LIBFT_PATH					=			./libft
LIBFT						=			$(LIBFT_PATH)/libft.a

SRC							=			minishell.c \
										$(addprefix utils/, ft_error.c \
															ft_loop.c \
															ft_start.c \
															)

OBJ							=			$(SRC:%.c=%.o)

all:						$(NAME)

$(NAME):					$(OBJ)
							$(MAKE) -C $(LIBFT_PATH)
							$(CC) $(CCFLAGS) $(OBJ) $(RL) $(LIBFT) -o $(NAME)

clean:
							$(MAKE) -C $(LIBFT_PATH) clean
							$(RM) $(OBJ)

fclean:						clean
							$(MAKE) -C $(LIBFT_PATH) fclean
							$(RM) $(NAME)

re:							fclean all

.PHONY:						all clean fclean re