/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:54:48 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/27 23:12:35 by mpelazza         ###   ########.fr       */
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

	struct sigaction	ctrlc;
}			t_var;

//readline functions
void	rl_clear_history(void);
void	rl_replace_line(const char *text, int clear_undo);
//parsing
char	*ft_read_command(char *ret, t_var *v);
char	*ft_get_word(t_var *v, char *line, int *i);
t_list	**ft_parse_command(t_var *v);
//parsing_tools
int		ft_find_end_quote(char *s, int index);
int		ft_env_var_name_len(char *name);
int		ft_word_len(t_var *v, t_list *env, char *line);
//metacharacters
t_list	*ft_set_fd_cmd(void);
void	ft_close_fd_cmd(t_list *fd_cmd);
char	*ft_get_metachar(char *line, int *i);
int		ft_handle_metachar(t_var *v, char *line, int *i);
//builtin
	//cd
void	ft_cd(t_var *v, t_list *cmd, t_list *env);
int		ft_check_path(t_var *v, DIR *dir, char *path, char *fullpath);
void	ft_deleted_rep(t_var *v, char **paths, char *path, int *pri);
void	ft_change_dir(t_var *v, char **paths, char *path, int *pri);
void	ft_change_pwd(t_var *v, int *pri);
void	ft_update_env(t_list *env, t_var *v);
char    *ft_cut_path(char *pwd);
char	*ft_remove_private(char *pwd);
int		ft_check_pwd(t_var *v, char *fullpath);
void    ft_free_cd(char **paths, char *path, char *pwd);

void	ft_pwd(t_var *v);
void	ft_echo(t_list *cmd);
void	ft_export(t_var *v, t_list *cmd, t_list *env);
void	ft_unset(t_list *cmd, t_list *env);
void	ft_env(t_list *env);
void	ft_export_set_var(t_list **env, char *cmd);
int		ft_check_export(t_var *v, char *cmd);
//execution
void	ft_exec_builtin(t_var *v, t_list *cmd, t_list *env);
void	ft_execution(t_var *v, t_list *fd_cmd);
//signal
void	ft_init_signals(t_var *v);
void	ft_handle_ctrl_c(int signal);
void	ft_handle_ctrl_c_heredoc(int signal);
void	do_nothing(int signal);
//history
void	ft_history(t_var *v, t_list *cmd);
void	ft_get_history(char *line, t_var *v);
//utils
char	**ft_lst_to_strtab(t_list *lst);
int		ft_count_char(char *s, char c);
char	*ft_getenv(t_list *env, char *name);
int		ft_is_builtin(t_list *cmd);
char	*ft_get_path(t_list *env, char *cmd);
void	ft_free_var(t_var *v);
char	*gnl_heredoc(void);
int		ft_pipeline_exit_status(t_var *v, char *word, int *i[2]);

//errors
int		ft_parsing_error(t_var *v, char *token);
int		ft_exec_error(t_var *v, char *cause, char *error, int status);
int		ft_builtin_error(t_var *v, char *cmd, char *cause, char *error);
int		ft_get_exit_code(int status);

#endif