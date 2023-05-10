/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:24:24 by rferrero          #+#    #+#             */
/*   Updated: 2023/05/09 16:23:57 by rferrero         ###   ########.fr       */
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
	char				*cmd;
	char				*cmd_token;
	int					cmd_type;
	char				**env;
	char				**export;
	char				**path;
	int					status;
	int					stop;
	int					exit_code;
	t_token				*token_start;
	int					token_list_size;
	int					**fd;
	int					count_pipes;
	int					infile;
	int					outfile;
	int					stdin_copy;
	int					stdout_copy;
	char				*user;
	char				*rl_text;
	struct sigaction	sa;
	struct sigaction	sa_child;
	struct sigaction	sa_child_heredoc;
	struct sigaction	sa_parent;
	struct sigaction	sa_parent_heredoc;
	int					*pid;
	int					count_fork;
	int					aux_sig;
	char				*hd_delim;
	char				*input_hd;
	int					heredoc[2];
	int					end_loop;
}	t_program;

//  global variable
extern t_program	g_data;

//  utils/ft_builtin_cd.c
void		ft_cd(char **cmd);
int			ft_is_builtin_parent(char *input);

//  utils/ft_builtin_echo.c
void		ft_echo(char **cmd);
int			ft_echo_n(t_token *token);

//  utils/ft_builtin_env.c
int			var_exist(char *variable);
void		ft_add_var_env(char **new_variable);
void		ft_remove_var_env(char *new_variable);

//  utils/ft_builtin_env2.c
int			ft_env_size(char **env);
char		**ft_env_calloc(int size);
void		ft_print_env(char *cmd);
char		*find_var_value(char **env, char *var);

//  utils/ft_builtin_export.c
void		ft_export(char **cmd);
void		exportation(char *cmd);
void		ft_remove_var_export(char *var);

//  utils/ft_builtin_export2.c
void		ft_print_export(void);
void		ft_add_export(char *variable);
int			var_exist_export(char *var);
void		replace_var_export(char *var);

//  utils/ft_builtin_export3.c
void		ft_sort(char **export);
void		ft_add_prefix(char **export);
void		ft_handle_export_quotes(char **export, int j);
void		ft_put_value_quotes_matrix(char **export);
void		get_export(char **env);

//  utils/ft_builtin_pwd.c
void		ft_pwd(char *str);

//  utils/ft_builtin_unset.c
void		ft_unset_handler(char **str);

//  utils/ft_builtin.c
int			is_var_assigned(char *str);
int			ft_is_builtin_parent(char *input);
int			is_builtin(char **str);
int			ft_is_builtin_child(char *input);

//  utils/ft_error.c
void		ft_error(int arg, char *msg);
void		ft_exit(void);
void		ft_close_fds(void);
void		ft_error_perror(int arg);
void		ft_free_pid_fd(void);

//  utils/ft_free.c
void		ft_free_matrix(char **matrix);
void		ft_free_data(void);
void		ft_free_loop(void);
void		ft_free_matrix_int(int **matrix, int size);
void		ft_free_pointers(char *ptr1, char *ptr2);

//  utils/ft_free2.c
void		ft_heredoc_close_exit(void);

//  utils/ft_loop.c
void		ft_loop(void);
void		ft_loop_start(void);
int			ft_check_empty_line(void);
int			ft_check_eof_cmd(void);

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
void		ft_handle_unclosed_quotes(void);

//	utils/ft_execute_token_list.c
void		ft_execute_token_list(void);
void		ft_execute(t_token *token);
void		ft_execute_start(void);

//	utils/ft_cmd_path.c
char		*ft_test_path(int i, t_token *token);
char		*ft_get_cmd_path(t_token *token);
void		ft_cmd_not_found(char *cmd);

//	utils/ft_fork.c
void		ft_child_process(t_token *token, char *cmd_path);
void		ft_parent_process(int pid);
void		ft_exec_child_builtin(t_token *token, char *cmd_path);
void		ft_free_child_process(void);

//	utils/ft_input_output.c
int			ft_open_output_file(t_token *token);
int			ft_open_input_file(t_token *token);
void		ft_check_std_in_out(t_token *token);
void		ft_redirect_infile(void);
void		ft_get_input_file(t_token *token);
int			handle_redirections(t_token *token);

//	utils/ft_pipe.c
void		redirect_to_pipe(void);
void		redirect_from_pipe(int type);
void		ft_open_pipe(void);
void		ft_close_pipes(t_token *token);

//  utils/ft_quote_handler.c
void		quotes_replace(t_token *token);
void		finishe_quote_replace(t_token *token, int *i, char **tmp, int *m);
void		ft_quotes_handler(void);

//  utils/ft_quote_handler2.c
void		ft_check_empty_token(t_token *token, int *i);
void		check_if_var(char *str, int *n, char *tmp, int *m);
void		ft_single_quotes(int *n, int *m, char *cmd, char **tmp);

//  utils/ft_quote_handler3.c
void		ft_exit_code_handler(int *n, char *tmp, int *m);
int			ft_strange_chars(int c);

//  utils/ft_quote_handler4.c
void		ft_double_quotes(int *n, int *m, char *cmd, char **tmp);
void		ft_handle_dolar_on_double(char *str, int *n, char **tmp, int *m);
void		ft_no_quotes(int *n, int *m, char *cmd, char **tmp);
void		ft_handle_dolar_no_quotes(char *str, int *n, char **tmp, int *m);

//	utils/ft_fork.c
void		ft_child_process(t_token *token, char *cmd_path);
void		ft_exec_child_builtin(t_token *token, char *cmd_path);
void		ft_free_child_process(void);
void		ft_wait_children(void);
void		ft_fork(char *cmd_path, t_token *token);

//	ft_signals.c
void		handle_sigint_empty(int sig);
void		handle_sig_child(int sig);
void		handle_sig_child_heredoc(int sig);
void		handle_sig_parent_heredoc(int sig);

// ft_signals_aux.c
void		ft_signals_exit_code(int wstatus);
void		ft_signal_setup(void);

//ft_syntax_error.c
int			ft_check_sintax(void);

//ft_heredoc.c
void		ft_execute_heredoc(t_token *token);
void		ft_heredoc_child(t_token *token);
void		ft_write_heredoc(void);
void		ft_heredoc_eof(void);
void		ft_heredoc_parent(int pid, t_token *token);

//ft_executable.c
int			ft_check_slash(char *str);
int			ft_is_executable(t_token *token);

//ft_utils.c
char		**ft_check_args_after_redirection(t_token *token);
char		**ft_new_cmd(t_token *token);
int			ft_is_export_wo_arg(t_token *token);
t_token		*ft_next_pipe(t_token *token);

#endif