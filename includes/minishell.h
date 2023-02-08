/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:54:48 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/08 02:28:55 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include "libft/libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_var
{
	t_list	**cmd;
	t_list	*env;
	t_list	*fd_cmd;

	pid_t	process;

	char	**path;
	char	*line;

}				t_var;

//global variable
//t_var	g_v;

//parsing
char	*ft_read_command(char *ret);
char	*ft_get_word(t_var *v, char *line, int *i);
t_list	**ft_parse_command(t_var *v);
//parsing_tools
int		ft_find_end_quote(char *s, int index);
int		ft_env_var_name_len(char *name);
int		ft_word_len(t_list *env, char *line);
//metacharacters
t_list	*ft_set_fd_cmd(void);
void	ft_close_fd_cmd(t_list *fd_cmd);
char	*ft_get_metachar(char *line, int *i);
int		ft_handle_metachar(t_var *v, char *line, int *i);
//builtin
void	ft_echo(t_list *cmd);
void	ft_pwd(void);
void	ft_export(t_list *cmd, t_list *env);
void	ft_unset(t_list *cmd, t_list *env);
void	ft_env(t_list *env);
void    ft_cd(t_list *cmd, t_list *env);
//execution
void	ft_execution(t_var *v, t_list *fd_cmd);
//signal
void	ft_sig_handler(int signal);
//utils
char	**ft_list_to_string_tab(t_list *lst);
int		ft_count_char(char *s, char c);
char	*ft_getenv(t_list *env, char *name);
int		ft_is_builtin(t_list *cmd);
void	ft_exec_builtin(t_list *cmd, t_list *env);
//errors
void	ft_put_errors(char *cause, char *details, char *msg, int is_exit);

#endif