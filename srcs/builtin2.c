/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:47:05 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/21 21:23:55 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_symbolic_links(t_var *v, char *path)
{
	struct stat	path_stat;

	lstat(path, &path_stat);
	if (S_ISLNK(path_stat.st_mode))
	{
		if (path_stat.st_nlink > 1)
		{
			ft_builtin_error(v, "cd", path,
				"Too many levels of symbolic links");
			return (0);
		}
	}
	return (1);
}

int	check_is_dir_and_perm(t_var *v, char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		ft_builtin_error(v, "cd", path, "Not a directory");
		return (0);
	}
	if (S_ISDIR(path_stat.st_mode) && !(path_stat.st_mode & S_IRUSR))
	{
		ft_builtin_error(v, "cd", path, "Permission denied");
		return (0);
	}
	return (1);
}

int	check_path(t_var *v, DIR *dir, char *path)
{
	if (!check_symbolic_links(v, path))
		return (0);
	if (dir)
	{
		closedir(dir);
		if (!check_is_dir_and_perm(v, path))
			return (0);
		return (1);
	}
	else
	{
		if (!check_is_dir_and_perm(v, path))
			return (0);
		ft_builtin_error(v, "cd", path, "No such file or directory");
		return (0);
	}
}

void	ft_change_pwd(t_list *env)
{
	char	*pwd;

	pwd = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
	while (env)
	{
		if (!ft_strncmp((char *)env->content, "PWD=", 4))
		{
			free(env->content);
			env->content = (void *)pwd;
			return ;
		}
		env = env->next;
	}
}

void	ft_cd(t_var *v, t_list *cmd, t_list *env)
{
	char	*path;
	char	*root;

	root = ft_getenv(env, "HOME");
	if (!cmd)
		path = ft_strdup(root);
	else
		path = ft_strdup((char *)cmd->content);
	if (path[0] == '~' && path[1] && path[1] == '/')
	{
		free(path);
		path = ft_strjoin(root, (char *)cmd->content + 1);
	}
	else if (path[0] == '~' && ft_strlen(path) == 1)
	{
		free(path);
		path = ft_strdup(root);
	}
	if (check_path(v, opendir(path), path))
		chdir(path);
	ft_change_pwd(env);
	free(path);
}
