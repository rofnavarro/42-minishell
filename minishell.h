/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:24:24 by rferrero          #+#    #+#             */
/*   Updated: 2023/03/23 15:25:57 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//  printf()
# include <stdio.h>

//  malloc()  free()  exit()  getenv()
# include <stdlib.h>

//  signal()  sigaction()  sigemptyset()  sigaddset()  kill()
# include <signal.h>

//  write()  access()  read() close()  fork()  getcwd()  chdir()  unlink()
//  execve()  dup()  dup2()  pipe()  isatty()  ttyname() ttyslot()
# include <unistd.h>

//  strerror()
# include <string.h>

//  perror()
# include <errno.h>

//  readline()  rl_clear_history()  rl_on_new_line()  rl_replace_line()
//  rl_redisplay()  add_history()
# include <readline/readline.h>
# include <readline/history.h>

//  open()  stat()  lstat()  fstat()
# include <sys/stat.h>
# include <fcntl.h>

//  wait()  waitpid()  wait3()  wait4()
# include <sys/wait.h> 

//  opendir()  readdir()  closedir()
# include <sys/types.h>
# include <dirent.h>

//  ioctl()
# include <sys/ioctl.h>

// tcsetattr()  tcgetattr()
# include <termios.h>

// tgetent()  tgetflag()  tgetnum()  tgetstr()  tgoto()  tputs()
# include <curses.h>
# include <term.h>

//  libft.a
# include "./libft/libft.h"

//  token
# include "./token.h"

typedef struct s_program
{
	char	*cmd;
	char	*cmd_token;
	char	**env;
	char	**path;
	int		status;
	int		stop;
	t_token	*token_start;
}	t_program;

//  utils/ft_builtin_cd.c
void		ft_cd(char *str, t_program *g_data);

//  utils/ft_builtin_env.c
void		ft_add_var_env(char *new_variable, t_program *g_data);
void		ft_remove_var_env(char *new_variable, t_program *g_data);

//  utils/ft_builtin_env2.c
int			ft_env_size(char **env);
char		**ft_env_calloc(int size);
void		ft_print_env(char *cmd, t_program *g_data);

//  utils/ft_builtin_pwd.c
void		ft_pwd(char *str, t_program *g_data);

//  utils/ft_builtin.c
void		is_builtin(char *str, t_program *g_data);

//  utils/ft_error.c
void		ft_error(char *msg, int arg);
void		ft_exit(t_program *g_data);

//  utils/ft_free.c
void		ft_free_matrix(char **matrix);
void		ft_free_data(t_program *g_data);

//  utils/ft_init.c
void		ft_init(t_program *g_data);

//  utils/ft_loop.c
void		ft_loop(t_program *g_data);

//  utils/ft_start.c
void		ft_start(char **env, t_program *g_data);

//  utils/ft_strtok.c
char		*ft_strtok(char *str, const char *delim);

//  utils/token_list.c
void		ft_add_token(t_program *g_data, char *cmd_token, t_type cmd_type);
void		ft_print_token_list(t_program *g_data);
void		ft_free_token_list(t_program *g_data, t_token *token, int start);

#endif