/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:04:35 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/22 18:10:14 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_metachar(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*i += 2;
		return (">>");
	}
	else if (line[*i] == '>')
	{
		*i += 1;
		return (">");
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*i += 2;
		return ("<<");
	}
	else if (line[*i] == '<')
	{
		*i += 1;
		return ("<");
	}
	else if (line[*i] == '|')
		return ("|");
	return (NULL);
}

int	ft_pipeline_exit_status(t_var *v, char *word, int *i[2])
{
	int	j;

	*i[0] += 2;
	if (!word)
		return (ft_strlen(v->strings->pipeline_exit_status));
	j = 0;
	while (v->strings->pipeline_exit_status[j])
		word[(*i[1])++] = v->strings->pipeline_exit_status[j++];
	return (0);
}

int	ft_get_exit_code(int status)
{
	if (status == 0)
		return (0);
	else if (status > 0)
		return (status / 256);
	else
	{
		status = -status - 1;
		return (255 - (status / 256));
	}
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

int	*ft_open_file(char *metachar, char *filename, int fd_cmd[2])
{
	if (!ft_strcmp(metachar, "<"))
		fd_cmd[0] = open(filename, O_RDONLY);
	else if (!ft_strcmp(metachar, ">>"))
		fd_cmd[1] = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (!ft_strcmp(metachar, ">"))
		fd_cmd[1] = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fd_cmd);
}
