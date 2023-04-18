# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 13:12:03 by rferrero          #+#    #+#              #
#    Updated: 2023/04/18 17:51:37 by rferrero         ###   ########.fr        #
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
															ft_builtin_echo.c \
															ft_builtin_env.c \
															ft_builtin_env2.c \
															ft_builtin_export.c \
															ft_builtin_pwd.c \
															ft_builtin.c \
															ft_check_quotes.c \
															ft_error.c \
															ft_execute_token_list.c \
															ft_free.c \
															ft_loop.c \
															ft_start.c \
															ft_strtok.c \
															ft_token_list.c \
															ft_cmd_path.c \
															ft_input_output.c \
															ft_pipe.c \
															ft_fork.c \
															ft_signals.c \
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