/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rferrero@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:24:24 by rferrero          #+#    #+#             */
/*   Updated: 2023/02/28 16:55:32 by rferrero         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>

//  wait()  waitpid()  wait3()  wait4()
# include <sys/wait.h> 

//  opendir()  readdir()  closedir()
# include <dirent.h>
# include <sys/types.h>

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
	char	**env;
	char	**path;
	int		status;
	int		stop;
}	t_program;

//  utils/ft_error.c
void		ft_error(char *msg, int arg);
void		ft_exit(t_program *g_data);

//  utils/ft_start.c
void		ft_start(char **env, t_program *g_data);

#endif