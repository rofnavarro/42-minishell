# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rinacio <rinacio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 13:12:03 by rferrero          #+#    #+#              #
#    Updated: 2023/03/27 15:21:43 by rinacio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						=			minishell

CC							=			cc
CCFLAGS						=			-Wall -Wextra -Werror

RL							=			-lreadline

RM							=			rm -rf

LIBFT_PATH					=			./libft
LIBFT						=			$(LIBFT_PATH)/libft.a

SRC							=			minishell.c \
										$(addprefix utils/, ft_builtin_cd.c \
															ft_builtin_pwd.c \
															ft_error.c \
															ft_free.c \
															ft_init.c \
															ft_loop.c \
															ft_start.c \
															ft_strtok.c \
															token_list.c \
															ft_check_quotes.c \
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