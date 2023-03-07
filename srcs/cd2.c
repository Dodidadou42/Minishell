/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:46:26 by ddychus           #+#    #+#             */
/*   Updated: 2023/03/03 10:46:29 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_update_env(t_list *env, t_var *v)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, "PWD=", 4))
		{
			free(tmp->content);
			tmp->content = ft_strdup(v->strings->pwd);
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, "OLDPWD=", 7))
		{
			free(tmp->content);
			tmp->content = ft_strdup(v->strings->old_pwd);
		}
		tmp = tmp->next;
	}
}

char	*ft_remove_private(char *pwd)
{
	char	*ret;

	ret = ft_strjoin("PWD=", pwd + 12);
	free(pwd);
	return (ret);
}

void	ft_change_dir(char *path, int *pri)
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

void	ft_change_pwd(t_list *env, t_var *v, int pri)
{
	char	*pwd;

	free(v->strings->old_pwd);
	v->strings->old_pwd = ft_strjoin_free("OLD", v->strings->pwd, 2);
	pwd = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
	if (!pri && !ft_strncmp(pwd, "PWD=/private", 12))
		pwd = ft_remove_private(pwd);
	v->strings->pwd = ft_strdup(pwd);
	ft_update_env(env, v);
	free(pwd);
}

void	ft_free_cd(char *path, char **paths)
{
	int	i;

	i = -1;
	free(path);
	while (paths[++i])
		free(paths[i]);
	free(paths);
}
