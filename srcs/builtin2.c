/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:47:05 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/09 00:00:59 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_symbolic_links(char *path, char *error)
{
	struct stat	path_stat;

	lstat(path, &path_stat);
	if (S_ISLNK(path_stat.st_mode))
	{
		if (path_stat.st_nlink > 1)
		{
			error = ft_strjoin(path, ": Too many levels of symbolic links");
			ft_put_errors("cd", 0, error, 0);
			free(error);
			return (0);
		}
	}
	return (1);
}

int	check_is_dir_and_perm(char *path, char *error)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		error = ft_strjoin(path, ": Not a directory");
		ft_put_errors("cd", 0, error, 0);
		free(error);
		return (0);
	}
	if (S_ISDIR(path_stat.st_mode) && !(path_stat.st_mode & S_IRUSR))
	{
		error = ft_strjoin(path, ": Permission denied");
		ft_put_errors("cd", 0, error, 0);
		free(error);
		return (0);
	}
	return (1);
}

int	check_path(DIR *dir, char *path)
{
	char	*error;

	error = NULL;
	if (!check_symbolic_links(path, error))
		return (0);
	if (dir)
	{
		closedir(dir);
		if (!check_is_dir_and_perm(path, error))
			return (0);
		return (1);
	}
	else
	{
		if (!check_is_dir_and_perm(path, error))
			return (0);
		error = ft_strjoin(path, ": No such file or directory");
		ft_put_errors("cd", 0, error, 0);
		free(error);
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
		}
		env = env->next;
	}
}

void	ft_cd(t_list *cmd, t_list *env)
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
	if (check_path(opendir(path), path))
		chdir(path);
	ft_change_pwd(env);
	free(path);
}

//j'ai changer ca pcq ya deja une variable HOME qui contient le path
// apres faut voir si elle est aussi a l'ecole mais je pense
//		root = ft_strjoin("/Users/", ft_getenv(env, "LOGNAME"));
//---->	root = ft_getenv(env, HOME);
//		free(root); ----> supprimer		 comme il est plus malloc

//j'ai aussi rajouter une petite fonction pour mettre a jour le pwd dans l'env

//Sinon c'est carre j'ai pas reussi a la casser pour le moment bien joue mec