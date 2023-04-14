/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rinacio <rinacio@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:24:24 by rferrero          #+#    #+#             */
/*   Updated: 2023/04/14 22:49:06 by rinacio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//  printf()  perror()
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

//  error.h
# include "./error.h"

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
	int		fd[2][2];
	int		count_pipes;
	int		infile;
	int		outfile;
	int		stdin_copy;
	int		stdout_copy;
	char	*user;
}	t_program;

//  global variable
extern t_program	g_data;

//  utils/ft_builtin_cd.c
void		ft_cd(char **cmd);

//  utils/ft_builtin_echo.c
void		ft_echo(char **cmd);

//  utils/ft_builtin_env.c
int			var_exist(char *variable);
void		ft_add_var_env(char **new_variable);
void		ft_remove_var_env(char **new_variable);

//  utils/ft_builtin_env2.c
int			ft_env_size(char **env);
char		**ft_env_calloc(int size);
void		ft_print_env(char *cmd);
char		*find_var_value(char **env, char *var);

//  utils/ft_builtin_pwd.c
void		ft_pwd(char *str);

//  utils/ft_builtin.c
int			is_builtin(char **str);
int			ft_is_builtin_child(char *input);

//  utils/ft_error.c
void		ft_error(int arg, char *msg);
void		ft_exit(void);

//  utils/ft_free.c
void		ft_free_matrix(char **matrix);
void		ft_free_data(void);
void		ft_free_loop(void);

//  utils/ft_loop.c
void		ft_loop(void);

//  utils/ft_start.c
void		get_path(void);
void		ft_start(char **env);

//  utils/ft_strtok.c
char		*ft_strtok(char *str, const char *delim);

//  utils/token_list.c
void		ft_add_token(char *cmd_token, t_type cmd_type);
void		ft_print_token_list(void);
void		ft_free_token_list(t_token *token, int start);
char		**ft_token_quotes(char **cmd);

//	utils/ft_check_quotes.c
int			ft_check_quotes(char *arg);
char		*ft_switch_inside_quotation(char *str);

//	utils/ft_execute_token_list.c
void		ft_execute_token_list(void);
void		ft_execute(t_token *token);

//	utils/ft_cmd_path.c
char		*ft_test_path(int i, t_token *token);
char		*ft_get_cmd_path(t_token *token);
void		ft_cmd_not_found(char *cmd);

//	utils/ft_input_output.c
void		ft_open_output_file(t_token *token);
void		ft_get_input_file(t_token *token);
void		ft_open_input_file(t_token *token);
void		ft_check_std_in_out(t_token *token);

//	utils/ft_pipe.c
void		redirect_to_pipe(void);
void		redirect_from_pipe(int type);
void		ft_open_pipe(void);
void		ft_close_pipes(t_token *token);

//	utils/ft_fork.c
void		ft_child_process(t_token *token, char *cmd_path);
void		ft_parent_process(int pid);
void		ft_exec_child_builtin(t_token *token,  char *cmd_path);
void		ft_free_child_process(void);

#endif