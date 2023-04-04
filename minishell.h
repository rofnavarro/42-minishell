/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:24:24 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/04 00:47:30 by rferrero         ###   ########.fr       */
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

//  structs
typedef struct s_program
{
	char	*cmd;
	char	*cmd_token;
	int		cmd_type;
	char	**env;
	char	**path;
	int		status;
	int		stop;
	int		exit_code;
	t_token	*token_start;
}	t_program;

//  global variable
extern t_program	g_data;

//  utils/ft_builtin_cd.c
void		ft_export_add_env(char *var, char *var_name);
void		ft_check_cd_path(char *input_path);
void		ft_cd(char *str);

//  utils/ft_builtin_cd2.c
// void		ft_cd_back();
void		ft_cd_home();
// void		ft_cd_stay();

//  utils/ft_builtin_echo.c
void		ft_echo(char *cmd);

//  utils/ft_builtin_env.c
int			var_exist(char *variable, int size);
void		ft_add_var_env(char *new_variable);
void		ft_remove_var_env(char *new_variable);

//  utils/ft_builtin_env2.c
int			ft_env_size(char **env);
char		**ft_env_calloc(int size);
void		ft_print_env(char *cmd);
void		ft_find_var(char *find_var, char *env_var, int *found);

//  utils/ft_builtin_pwd.c
void		ft_pwd(char *str);

//  utils/ft_builtin.c
void		is_builtin(char *str);

//  utils/ft_error.c
void		ft_error(int arg);
void		ft_exit(void);

//  utils/ft_free.c
void		ft_free_matrix(char **matrix);
void		ft_free_data(void);

//  utils/ft_loop.c
void		ft_loop(void);

//  utils/ft_start.c
void		ft_start(char **env);

//  utils/ft_strtok.c
char		*ft_strtok(char *str, const char *delim);

//  utils/token_list.c
void		ft_add_token(char *cmd_token, t_type cmd_type);
void		ft_print_token_list(void);
void		ft_free_token_list(t_token *token, int start);

//	utils/ft_check_quotes.c
int			ft_check_quotes(char *arg);
char		*ft_switch_inside_quotation(char *str);

//	utils/ft_execute_token_list.c
void		ft_execute_token_list(void);
void		ft_execute(t_token *token);
char		*ft_get_cmd_path(t_token *token);
char		*ft_test_path(int i, t_token *token);

#endif