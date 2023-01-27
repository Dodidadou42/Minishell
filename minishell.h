#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_var
{
    char    *line;

    char    **paths;

    pid_t   pid_main;

}   t_var;

char	*get_next_line(int fd);

void	exec(char *argv, char **env);


int	msg(char *err);
void	error_msg(char *error);

void	ft_putstr(char *str);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split_doublequote(char const *s, char c);
char	**ft_split_quote(char const *s, char c);
char	**ft_split(char const *s, char c);
int	ft_strchr(const char *str, int searchedChar);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int	ft_strncmp(char *str1, char *str2, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);

#endif