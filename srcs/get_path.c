/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:39:12 by mpelazza          #+#    #+#             */
/*   Updated: 2023/01/27 16:06:37 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path;
	char	*temp;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (0);
}

/*void	exec(char *argv, char **env)
{
	char	**cmd;
	char	*path;
	int		i;

	i = -1;
	cmd = get_cmd(argv);
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd + 1);
	else
	{
		path = get_path(cmd[0], env);
		if (!path)
		{
			printf("command not found: %s", cmd[0]);
			while (cmd[++i])
				free(cmd[i]);
			free(cmd);
			exit(127);
		}
		if (execve(path, cmd, env) == -1)
			ft_put_errors("couldn't execute.", 0, 0);
	}
}*/