#include "minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, (str + i), 1);
}

void	error_msg(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}