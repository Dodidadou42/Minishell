/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:50:10 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/22 16:52:13 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*ft_free_null(char *s)
{
	free(s);
	return (NULL);
}

int	ft_check_exec_is_dir(t_var *v, char *s)
{
	DIR	*dir;

	dir = opendir(s);
	if (dir)
	{
		ft_exec_error(v, s, "is a directory", 127);
		closedir(dir);
		return (1);
	}
	return (0);
}
