/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:18:35 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/17 21:59:42 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_lst_to_strtab(t_list *lst)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		tab[i++] = ft_strdup((char *)lst->content);
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_count_char(char *s, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i] == c)
			++count;
	return (count);
}

char	*ft_getenv(t_list *env, char *name)
{
	char	*cast;
	int		len;

	len = 0;
	while (name[len] && name[len] != '=')
		++len;
	while (env)
	{
		cast = (char *)env->content;
		if (!ft_strncmp(cast, name, len))
		{	
			if (!cast[len])
				return ("");
			else if (cast[len] == '=')
				return (&cast[len + 1]);
		}
		env = env->next;
	}
	return (NULL);
}

int	ft_is_builtin(t_list *cmd)
{
	if (!ft_strcmp((char *)cmd->content, "echo")
		|| !ft_strcmp((char *)cmd->content, "cd")
		|| !ft_strcmp((char *)cmd->content, "pwd")
		|| !ft_strcmp((char *)cmd->content, "export")
		|| !ft_strcmp((char *)cmd->content, "unset")
		|| !ft_strcmp((char *)cmd->content, "env")
		|| !ft_strcmp((char *)cmd->content, "history")
		|| !ft_strcmp((char *)cmd->content, "exit")
		|| (ft_strchr((char *)cmd->content, '=')
			&& ft_check_export(NULL, (char *)cmd->content, NULL)))
		return (1);
	return (0);
}

char	*ft_get_path(t_list *env, char *cmd)
{
	char	**paths;	
	char	*tmp;
	int		i;

	if (!access(cmd, F_OK) && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(ft_getenv(env, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin_free(paths[i], ft_strjoin("/", cmd), 2);
		if (!access(tmp, F_OK))
		{
			ft_split_free(paths);
			return (tmp);
		}
		free(tmp);
	}
	ft_split_free(paths);
	return (NULL);
}
