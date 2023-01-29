/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazzas <mpelazza@student.42nice.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:40:13 by mpelazzas         #+#    #+#             */
/*   Updated: 2023/01/27 13:40:15 by mpelazzas        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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