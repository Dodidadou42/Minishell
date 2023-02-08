/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:56:20 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/08 02:23:46 by mpelazza         ###   ########.fr       */
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

void	ft_process(t_var *v, int cmd_i, int fd_cmd[2], int fd_pipe[2])
{
	v->process = fork();
	if (v->process == 0)
	{
		close(fd_pipe[0]);
		if (fd_cmd[0] != 0)
			dup2(fd_cmd[0], STDIN);
		if (fd_cmd[1] != 1)
			dup2(fd_cmd[1], STDOUT);
		else if (v->cmd[cmd_i + 1])
			dup2(fd_pipe[1], STDOUT);
		ft_exec_cmd(v, v->cmd[cmd_i], ft_list_to_string_tab(v->cmd[cmd_i]),
			ft_list_to_string_tab(v->env));
	}
	else
	{
		waitpid(v->process, NULL, 0);
		close(fd_pipe[1]);
	}
}

// Aucun builtin ne prend d'entree donc en vrai pas obliger 
// de les gerees mais bon ca coute rien
void	ft_builtin(t_var *v, int cmd_i, int fd_cmd[2], int fd_pipe[2])
{
	int	intput_save;
	int	output_save;

	intput_save = dup(STDIN);
	output_save = dup(STDOUT);
	if (fd_cmd[0] != 0)
		dup2(fd_cmd[0], STDIN);
	if (fd_cmd[1] != 1)
		dup2(fd_cmd[1], STDOUT);
	else if (v->cmd[cmd_i + 1])
		dup2(fd_pipe[1], STDOUT);
	ft_exec_builtin(v->cmd[cmd_i], v->env);
	close(fd_pipe[1]);
	dup2(intput_save, STDIN);
	dup2(output_save, STDOUT);
}

void	ft_execution(t_var *v, t_list *fd_cmd)
{
	int	fd_pipe[2];
	int	*fd_cmd_cast;
	int	i;

	i = -1;
	fd_cmd_cast = (int *)fd_cmd->content;
	while (v->cmd[++i])
	{
		pipe(fd_pipe);
		if (ft_is_builtin(v->cmd[i]))
			ft_builtin(v, i, fd_cmd_cast, fd_pipe);
		else
			ft_process(v, i, fd_cmd_cast, fd_pipe);
		if (v->cmd[i + 1])
		{
			fd_cmd = fd_cmd->next;
			fd_cmd_cast = (int *)fd_cmd->content;
			if (fd_cmd_cast[0] == 0)
				fd_cmd_cast[0] = fd_pipe[0];
			else
				close(fd_pipe[0]);
		}
	}
}
