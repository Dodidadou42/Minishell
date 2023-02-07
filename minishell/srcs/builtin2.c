/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:47:05 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/02 06:47:11 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_logname(t_list *env)
{
    char    *logname;

    while(env && ft_strncmp("LOGNAME=", (char *)env->content, 8))
        env = env->next;
    logname = ft_strdup((char *)env->content + 8);
    return (logname);
}

void    check_dir(DIR *dir, char *path)
{
    char    *error;

    error = NULL;
    if (dir)
    {
        closedir(dir);
        chdir(path);
    }
    else 
    {
        error = ft_strjoin("no such file or directory: ", path);
        ft_put_errors("cd", 0, error, 0);
        free(error);
    }
}

void    ft_cd(t_list *cmd, t_list *env)
{
    char    *path;
    char    *root;

    root = ft_strjoin_free("/Users/", get_logname(env), 2);
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
    check_dir(opendir(path), path);
    free(path);
    free(root);
}
    //cd fonctionne correctement, je crois gérer tous les leaks
    // a voir si on trouve des cas tres particuliers sur le bash, chatgpt
    // a parlé des problemes dautorisations et tout je check ca demain