/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:48:12 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/08 23:19:40 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_path(t_list *env, char *cmd)
{
	char	**paths;	
	char	*tmp;
	int		i;

	paths = ft_split(ft_getenv(env, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin_free(paths[i], ft_strjoin("/", cmd), 2);
		if (!access(tmp, F_OK))
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

void	ft_exec_cmd(t_var *v, t_list *cmd, char **args, char **envp)
{
	char	*path;

	path = ft_get_path(v->env, (char *)cmd->content);
	if (!path)
	{
		ft_split_free(args);
		ft_split_free(envp);
		ft_put_errors((char *)cmd->content, NULL, "command not found", 127);
	}
	execve(path, args, envp);
	ft_split_free(args);
	ft_split_free(envp);
	ft_put_errors((char *)cmd->content, NULL, "permission denied", 126);
}

void	ft_exec_process(t_var *v, t_list *cmd, int fd_pipe[2])
{
	v->process = fork();
	if (v->process == 0)
	{
		close(fd_pipe[0]);
		ft_exec_cmd(v, cmd, ft_lst_to_strtab(cmd), ft_lst_to_strtab(v->env));
	}
	else
		waitpid(v->process, NULL, 0);
}

int	ft_setup_n_launch(t_var *v, int std_save[2], int fd_cmd[2], int i)
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	if (fd_cmd[0] != 0)
		dup2(fd_cmd[0], STDIN);
	if (fd_cmd[1] != 1)
		dup2(fd_cmd[1], STDOUT);
	else if (i + 1 < v->pipe_count)
		dup2(fd_pipe[1], STDOUT);
	if (v->cmd[i] && ft_is_builtin(v->cmd[i]))
		ft_exec_builtin(v->cmd[i], v->env);
	else if (v->cmd[i])
		ft_exec_process(v, v->cmd[i], fd_pipe);
	close(fd_pipe[1]);
	dup2(std_save[0], STDIN);
	dup2(std_save[1], STDOUT);
	return (fd_pipe[0]);
}

void	ft_execution(t_var *v, t_list *fd_cmd)
{
	int	std_save[2];
	int	*fd_cmd_cast;
	int	fd_pipe_out;
	int	i;

	std_save[0] = dup(STDIN);
	std_save[1] = dup(STDOUT);
	i = -1;
	while (++i < v->pipe_count)
	{
		fd_pipe_out = ft_setup_n_launch(v, std_save, (int *)fd_cmd->content, i);
		fd_cmd = fd_cmd->next;
		if (fd_cmd)
		{
			fd_cmd_cast = (int *)fd_cmd->content;
			if (fd_cmd_cast[0] == 0)
				fd_cmd_cast[0] = fd_pipe_out;
			else
				close(fd_pipe_out);
		}
		else
			close(fd_pipe_out);
	}
	close(std_save[0]);
	close(std_save[1]);
}
