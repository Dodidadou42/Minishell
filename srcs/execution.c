/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 02:41:47 by mpelazza          #+#    #+#             */
/*   Updated: 2023/04/12 04:38:32 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_builtin(t_var *v, t_list *cmd, t_list *env)
{
	if (!ft_strcmp((char *)cmd->content, "echo"))
		ft_echo(cmd->next);
	else if (!ft_strcmp((char *)cmd->content, "history"))
		ft_history(v, cmd->next);
	else if (!ft_strcmp((char *)cmd->content, "cd") && !v->pipe_count)
		ft_cd(v, cmd->next, env);
	else if (!ft_strcmp((char *)cmd->content, "pwd"))
		ft_pwd(v);
	else if (!ft_strcmp((char *)cmd->content, "export")
		&& (!v->pipe_count || !cmd->next))
		ft_export(v, cmd->next, env);
	else if (!ft_strcmp((char *)cmd->content, "unset"))
		ft_unset(v, cmd->next, &env);
	else if (!ft_strcmp((char *)cmd->content, "env"))
		ft_env(env);
	else if (!ft_strcmp((char *)cmd->content, "exit") && !v->pipe_count)
		ft_exit(v, cmd->next);
	while (!v->pipe_count && cmd && ft_strchr((char *)cmd->content, '=')
		&& ft_check_export(NULL, (char *)cmd->content, NULL))
	{
		ft_assignation(v, (char *)cmd->content);
		cmd = cmd->next;
	}
}

void	ft_exec_cmd(t_var *v, t_list *cmd, char **args, char **envp)
{
	char	*path;
	int		check;

	path = ft_get_path(v->env, (char *)cmd->content);
	if (!path)
	{
		ft_split_free(args);
		ft_split_free(envp);
		if (ft_strchr((char *)cmd->content, '/'))
			ft_exec_error(v, (char *)cmd->content,
				"No such file or directory", 127);
		else
			ft_exec_error(v, (char *)cmd->content, "command not found", 127);
		exit(127);
	}
	check = ft_check_exec_is_dir(v, (char *)cmd->content);
	if (!check)
		execve(path, args, envp);
	free(path);
	ft_split_free(args);
	ft_split_free(envp);
	if (!check)
		ft_exec_error(v, (char *)cmd->content, "permission denied", 126);
	exit(check);
}

void	ft_exec_fork(t_var *v, int fd_pipe[2], int i)
{
	g_sig->n = 1;
	v->process = fork();
	g_sig->pid = v->process;
	if (v->process == 0)
	{
		close(fd_pipe[0]);
		ft_exec_cmd(v, v->cmd[i], ft_lst_to_strtab(v->cmd[i]),
			ft_lst_to_strtab(v->env));
	}
}

void	ft_setup_exec(t_var *v, t_list *fd_cmd, int std_save[2], int i)
{
	int	fd_pipe[2];
	int	*fd_tmp;
	int	tmp;

	while (++i <= v->pipe_count)
	{
		pipe(fd_pipe);
		ft_setup_pipe(v, (int *)fd_cmd->content, fd_pipe, i);
		if (v->cmd[i] && ft_is_builtin(v->cmd[i]))
			ft_exec_builtin(v, v->cmd[i], v->env);
		else if (v->cmd[i])
			ft_exec_fork(v, fd_pipe, i);
		close(fd_pipe[1]);
		if (i > v->pipe_start + 1)
			close(tmp);
		dup2(std_save[0], STDIN);
		dup2(std_save[1], STDOUT);
		fd_tmp = (int *)fd_cmd->content;
		fd_cmd = fd_cmd->next;
		tmp = ft_pipe_redir(fd_cmd, fd_pipe);
	}
}

void	ft_execution(t_var *v)
{
	int	std_save[2];
	int	status;

	std_save[0] = dup(STDIN);
	std_save[1] = dup(STDOUT);
	ft_setup_exec(v, v->fd_cmd, std_save, v->pipe_start);
	waitpid(v->process, &status, 0);
	while (wait(NULL) > 0)
		continue ;
	ft_get_pipeline_exit_code(v, status);
	close(std_save[0]);
	close(std_save[1]);
}
