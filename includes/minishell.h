/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:54:48 by mpelazza          #+#    #+#             */
/*   Updated: 2023/04/05 05:02:08 by mpelazza         ###   ########.fr       */
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
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include "libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_signals
{
	pid_t	pid;
	pid_t	child;
	int		n;
	int		bool_ctrlc;
}		t_gsig;

t_gsig	*g_sig;

typedef struct s_history
{
	char				*cmd;

	int					offset;

	struct s_history	*next;
}		t_histo;

typedef struct s_strings
{
	char				*line;
	char				*pipeline_exit_status;
	char				*pwd;
	char				*old_pwd;
	char				*root;
}		t_strings;

typedef struct s_var
{
	t_list				**cmd;
	t_list				*env;
	t_list				*export;
	t_list				*fd_cmd;

	t_histo				*histo;

	t_strings			*strings;

	pid_t				process;

	char				**path;

	int					pipe_start;
	int					pipe_count;
	int					cat_exception;
	int					bool_env;

	struct sigaction	ctrlc;
}			t_var;

//readline functions
void	rl_clear_history(void);
void	rl_replace_line(const char *text, int clear_undo);
//parsing
char	*ft_read_command(char *ret, t_var *v);
char	*ft_get_word(t_var *v, char *line, int *i, char start);
t_list	**ft_parse_command(t_var *v);
//parsing_tools
int		ft_find_end_quote(char *s, int index);
int		ft_env_var_name_len(char *name);
int		ft_word_len(t_var *v, t_list *env, char *line);
void	ft_check_readline(char *ret, t_var *v);
//metacharacters
int		ft_handle_metachar(t_var *v, char *line, int *i);
//builtin
void	ft_pwd(t_var *v);
void	ft_echo(t_list *cmd);
void	ft_unset(t_var *v, t_list *cmd, t_list **env);
void	ft_env(t_list *env);
void	ft_exit(t_var *v, t_list *cmd);
	//cd
void	ft_cd(t_var *v, t_list *cmd, t_list *env);
int		ft_check_path(t_var *v, DIR *dir, char *path, char *fullpath);
int		ft_cd_swap(t_var *v, char *path);
void	ft_deleted_rep(t_var *v, char **paths, char *path, int *pri);
void	ft_change_dir(t_var *v, char **paths, char *path, int *pri);
void	ft_change_pwd(t_var *v, int *pri);
void	ft_update_env(t_list *env, t_var *v);
char	*ft_cut_path(char *pwd);
int		ft_check_pwd(t_var *v, char *fullpath);
void	ft_free_cd(char **paths, char *path, char *pwd);
	//export
void	ft_export(t_var *v, t_list *cmd, t_list *env);
void	ft_export_set_var(t_list **env, char *cmd);
int		ft_check_export(t_var *v, char *cmd, char *cmd_name);
void	ft_assignation(t_var *v, char *a);
void	ft_setup_export(t_var *v, char *cmd, int len, t_list *export);
//execution
void	ft_execution(t_var *v);
//execution_utils
int		ft_is_builtin(t_list *cmd);
int		ft_check_exec_is_dir(t_var *v, char *s);
void	ft_get_pipeline_exit_code(t_var *v, int status);
void	ft_setup_pipe(t_var *v, int fd_cmd[2], int fd_pipe[2], int i);
int		ft_pipe_redir(t_list *fd_cmd, int fd_pipe[2]);
//signal
void	ft_init_signals(t_var *v);
void	ft_handle_ctrlc(int signal);
void	ft_handle_ctrl_c_heredoc(int signal);
void	do_nothing(int signal);
//history
void	ft_history(t_var *v, t_list *cmd);
void	ft_get_history(char *line, t_var *v);
//utils
char	**ft_lst_to_strtab(t_list *lst);
int		ft_count_char(char *s, char c);
char	*ft_getenv(t_list *env, char *name);
t_list	*ft_set_fd_cmd(void);
void	ft_close_fd_cmd(t_list *fd_cmd);
char	*ft_get_metachar(char *line, int *i);
int		ft_pipeline_exit_status(t_var *v, char *word, int *i[2]);
int		ft_get_exit_code(int status);
char	*ft_get_path(t_list *env, char *cmd);
int		*ft_open_file(char *metachar, char *filename, int fd_cmd[2]);
//errors
int		ft_parsing_error(t_var *v, char *token);
int		ft_exec_error(t_var *v, char *cause, char *error, int status);
int		ft_builtin_error(t_var *v, char *cmd, char *cause, char *error);

#endif