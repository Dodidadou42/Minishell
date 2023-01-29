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

# define ERROR  2
# define SP     0
# define DQ     1
# define Q      2

typedef struct s_cmd
{
    char            *s;
    int             type;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_var
{
    char    *line;

    char    **paths;

    pid_t   pid_main;

    t_cmd   *cmd;
    t_cmd   *cmd_untrimmed;

}   			t_var;


//MINISHELL
t_var	*init_var(t_var *v, char **env);
char	*read_command(void);
t_cmd	*parse_command(char *line);
void	exec(char *argv, char **env);
void    free_var(t_var *v);

//BUILTINS
void    ft_echo(char **args);

// LIBFT
void	ft_putstr(char *str);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
int		ft_strchr(const char *str, int searchedChar);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *str1, char *str2, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int     ft_strcmp(const char *s1, const char *s2);
char	*ft_join_free(char *s1, char const *s2);
char	*ft_strdup(const char *source);

//UTILS
int		msg(char *err);
void	ft_put_errors(char *cause, char *details, int is_exit);

//PARSE_COMMAND_UTILS
int     get_wordlen(char *line, int type);
int     is_space(char c);
t_cmd   *add_cmd(int n);
t_cmd	*trim_command(t_cmd *command);
void	print_cmd(t_cmd *cmd);


#endif