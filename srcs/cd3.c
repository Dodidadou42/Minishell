/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:55:23 by ddychus           #+#    #+#             */
/*   Updated: 2023/03/17 22:10:09 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_cd(char **paths, char *path, char *pwd)
{
	int	i;

	i = -1;
	free(path);
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if (pwd)
		free(pwd);
}

char	*ft_cut_path(char *pwd)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strrchr(pwd, '/');
	*tmp = '\0';
	ret = ft_strdup(pwd);
	free(pwd);
	return (ret);
}

char	*ft_remove_private(char *pwd)
{
	char	*ret;

	ret = ft_strjoin("PWD=", pwd + 12);
	free(pwd);
	return (ret);
}

void	ft_change_pwd(t_var *v, int *pri)
{
	char	*pwd;

	free(v->strings->old_pwd);
	v->strings->old_pwd = ft_strjoin_free("OLD", v->strings->pwd, 2);
	pwd = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
	if (!(*pri) && !ft_strncmp(pwd, "PWD=/private", 12))
		pwd = ft_remove_private(pwd);
	v->strings->pwd = ft_strdup(pwd);
	ft_update_env(v->env, v);
	free(pwd);
}

int	ft_check_pwd(t_var *v, char *fullpath)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_builtin_error(v, "cd", fullpath,
			"Error retrieving current directory: "
			"Parent directories may have been deleted");
		return (0);
	}
	free(pwd);
	return (1);
}
