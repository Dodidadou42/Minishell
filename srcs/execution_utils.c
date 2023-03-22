/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:24:06 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/22 18:12:46 by mpelazza         ###   ########.fr       */
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

t_list	*ft_cat_exception(t_var *v, int i, int count)
{
	t_list		*ret;
	int			*cast;
	struct stat	fd_stat;

	ret = v->fd_cmd;
	cast = (int *)ret->content;
	fstat(cast[0], &fd_stat);
	if (i < count && v->cmd[i] && !v->cmd[i]->next && !fd_stat.st_size
		&& !ft_strcmp((char *)v->cmd[i]->content, "cat"))
	{
		while (i < count && v->cmd[i] && !v->cmd[i]->next && !fd_stat.st_size
			&& !ft_strcmp((char *)v->cmd[i]->content, "cat"))
		{
			v->cat_exception += 1;
			v->pipe_start += 1;
			i += 1;
			ret = ret->next;
			cast = (int *)ret->content;
			fstat(cast[0], &fd_stat);
		}
	}
	return (ret);
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
	if (!v->cmd[v->pipe_start - 1])
	{
		free(v->strings->pipeline_exit_status);
		v->strings->pipeline_exit_status = ft_itoa(0);
	}
	else if (!ft_is_builtin(v->cmd[v->pipe_start - 1]))
	{
		free(v->strings->pipeline_exit_status);
		v->strings->pipeline_exit_status = ft_itoa(ft_get_exit_code(status));
	}
}

void	ft_setup_fd_pipe(t_var *v, int fd_cmd[2], int fd_pipe[2], int i)
{
	if (fd_cmd[0] != 0)
		dup2(fd_cmd[0], STDIN);
	if (fd_cmd[1] != 1)
		dup2(fd_cmd[1], STDOUT);
	else if (i < v->pipe_count)
		dup2(fd_pipe[1], STDOUT);
}
