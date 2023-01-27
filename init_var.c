#include "minishell.h"

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

t_var	*init_var(t_var *v, char **env)
{
	v = malloc(sizeof(t_var *));
	v->paths = get_paths(env);
	return (v);
}