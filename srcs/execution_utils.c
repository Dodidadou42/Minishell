/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:24:06 by mpelazza          #+#    #+#             */
/*   Updated: 2023/04/10 15:35:13 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_get_pipeline_exit_code(t_var *v, int status)
{
	if (!v->cmd[v->pipe_count])
	{
		free(v->strings->pipeline_exit_status);
		v->strings->pipeline_exit_status = ft_itoa(0);
	}
	else if (!ft_is_builtin(v->cmd[v->pipe_count]))
	{
		free(v->strings->pipeline_exit_status);
		v->strings->pipeline_exit_status = ft_itoa(ft_get_exit_code(status));
	}
}

void	ft_setup_pipe(t_var *v, int fd_cmd[2], int fd_pipe[2], int i)
{
	if (fd_cmd[0] != 0)
		dup2(fd_cmd[0], STDIN);
	if (fd_cmd[1] != 1)
		dup2(fd_cmd[1], STDOUT);
	else if (i < v->pipe_count)
		dup2(fd_pipe[1], STDOUT);
}

int	ft_pipe_redir(t_list *fd_cmd, int fd_pipe[2])
{
	int	*fd_cmd_cast;

	if (fd_cmd)
	{
		fd_cmd_cast = (int *)fd_cmd->content;
		if (fd_cmd_cast[0] == 0)
			fd_cmd_cast[0] = fd_pipe[0];
		else
			close(fd_pipe[0]);
		return (fd_cmd_cast[0]);
	}
	close(fd_pipe[0]);
	return (0);
}
