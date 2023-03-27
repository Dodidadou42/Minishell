/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:46:26 by ddychus           #+#    #+#             */
/*   Updated: 2023/03/23 18:08:52 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_update_env(t_list *env, t_var *v)
{
	ft_export_set_var(&env, ft_strdup(v->strings->pwd));
	ft_export_set_var(&env, ft_strdup(v->strings->old_pwd));
}

int	ft_cd_swap(t_var *v, char *path)
{
	char	*tmp;

	if (!ft_strncmp(path, "-", 1))
	{
		if (!ft_strcmp(path, "-"))
		{
			chdir(v->strings->old_pwd + 7);
			printf("%s\n", v->strings->old_pwd + 7);
			tmp = v->strings->pwd;
			v->strings->pwd = ft_strdup(v->strings->old_pwd + 3);
			free(v->strings->old_pwd);
			v->strings->old_pwd = ft_strjoin_free("OLD", tmp, 2);
			ft_update_env(v->env, v);
		}
		else
		{
			path[2] = '\0';
			ft_builtin_error(v, "cd", path, "invalid option");
		}
		free(path);
		return (0);
	}
	return (1);
}

void	ft_move_dir(char *path, int *pri)
{
	char	*pwd;

	chdir(path);
	pwd = getcwd(NULL, 0);
	if (!ft_strcmp(pwd, "/private") && *pri == 0
		&& ft_strcmp(path, "/private") && ft_strcmp(path, "private"))
		chdir("/");
	free(pwd);
	pwd = getcwd(NULL, 0);
	if (!ft_strcmp(pwd, "/"))
		*pri = 0;
	if (!ft_strcmp(path, "/private") || !ft_strcmp(path, "private"))
		*pri = 1;
	free(pwd);
}

void	ft_change_dir(t_var *v, char **paths, char *path, int *pri)
{
	int		i;

	i = -1;
	while (paths[++i])
	{
		if (!ft_check_path(v, opendir(paths[i]), paths[i], path))
		{
			ft_move_dir(v->strings->pwd, pri);
			return ;
		}
		ft_move_dir(paths[i], pri);
	}
	ft_change_pwd(v, pri);
}

void	ft_deleted_rep(t_var *v, char **paths, char *path, int *pri)
{
	char	*pwd;
	int		i;

	i = -1;
	pwd = ft_strdup(v->strings->pwd + 4);
	while (paths[++i])
	{
		if (!ft_strcmp(paths[i], ".."))
			pwd = ft_cut_path(pwd);
		else if (ft_strcmp(paths[i], "."))
		{
			pwd = ft_strjoin_free(pwd, "/", 1);
			pwd = ft_strjoin_free(pwd, paths[i], 1);
		}
	}
	if (ft_check_path(v, opendir(pwd), pwd, path))
	{
		ft_move_dir(pwd, pri);
		ft_change_pwd(v, pri);
	}
	free(pwd);
}
