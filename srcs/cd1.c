/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:47:05 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/01 09:21:08 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_is_dir_and_perm(t_var *v, char *path, char *fullpath)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		ft_builtin_error(v, "cd", fullpath, "Not a directory");
		return (0);
	}
	if (S_ISDIR(path_stat.st_mode) && !(path_stat.st_mode & S_IRUSR))
	{
		ft_builtin_error(v, "cd", fullpath, "Permission denied");
		return (0);
	}
	return (1);
}

int	ft_check_path(t_var *v, DIR *dir, char *path, char *fullpath)
{
	struct stat	path_stat;

	lstat(path, &path_stat);
	if (S_ISLNK(path_stat.st_mode) && path_stat.st_nlink > 1)
	{
		ft_builtin_error(v, "cd", fullpath,
			"Too many levels of symbolic links");
		return (0);
	}
	if (dir)
	{
		closedir(dir);
		if (!ft_check_is_dir_and_perm(v, path, fullpath))
			return (0);
		return (1);
	}
	else
	{
		if (ft_check_is_dir_and_perm(v, path, fullpath)
			&& ft_check_pwd(v, fullpath))
			ft_builtin_error(v, "cd", fullpath, "No such file or directory");
		return (0);
	}
}

int	ft_check_peculiar(t_var *v, char *path)
{
	if (!ft_strcmp(path, "//") || !ft_strcmp(path, "/"))
	{
		chdir(path);
		free(v->strings->old_pwd);
		v->strings->old_pwd = ft_strjoin_free("OLD", v->strings->pwd, 2);
		if (!ft_strcmp(path, "//"))
			v->strings->pwd = ft_strdup("PWD=//");
		else
			v->strings->pwd = ft_strdup("PWD=/");
		ft_update_env(v->env, v);
		free(path);
		return (0);
	}
	if (!ft_cd_swap(v, path))
		return (0);
	return (1);
}

char	*ft_get_real_path(t_var *v, t_list *cmd, t_list *env)
{
	char	*path;

	if (!cmd || (!ft_strncmp(cmd->content, "~", 1) && !v->bool_env))
	{
		if (ft_getenv(env, "HOME"))
			path = ft_strdup(ft_getenv(env, "HOME"));
		else
		{
			ft_builtin_error(v, "cd", "HOME", " not set");
			return (NULL);
		}
	}
	else
		path = ft_strdup((char *)cmd->content);
	if (path[0] == '~' && path[1] && path[1] == '/')
	{
		free(path);
		path = ft_strjoin(v->strings->root, (char *)cmd->content + 1);
	}
	else if (path[0] == '~' && !path[1])
	{
		free(path);
		path = ft_strdup(v->strings->root);
	}
	return (path);
}

void	ft_cd(t_var *v, t_list *cmd, t_list *env)
{
	char		*path;
	char		**paths;
	char		*pwd;
	static int	pri = 0;

	path = ft_get_real_path(v, cmd, env);
	if (!path || !ft_check_peculiar(v, path))
		return ;
	if (ft_strncmp(path, "/", 1))
		paths = ft_split(path, '/');
	else
	{
		paths = ft_split(path + 1, '/');
		paths[0] = ft_strjoin_free("/", paths[0], 2);
		pri = 0;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd && path[0] != '/')
		ft_deleted_rep(v, paths, path, &pri);
	else
		ft_change_dir(v, paths, path, &pri);
	ft_free_cd(paths, path, pwd);
}
