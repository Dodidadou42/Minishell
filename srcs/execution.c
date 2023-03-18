/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:48:12 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/18 15:35:25 by mpelazza         ###   ########.fr       */
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

	path = ft_get_path(v->env, (char *)cmd->content);
	if (!path)
	{
		ft_split_free(args);
		ft_split_free(envp);
		ft_exec_error(v, (char *)cmd->content, "command not found", 127);
		exit(127);
	}
	execve(path, args, envp);
	free(path);
	ft_split_free(args);
	ft_split_free(envp);
	ft_exec_error(v, (char *)cmd->content, "permission denied", 126);
	exit(126);
}

int	ft_setup_n_launch(t_var *v, int std_save[2], int fd_cmd[2], int i)
{
	int	fd_pipe[2];

	pipe(fd_pipe);
	if (fd_cmd[0] != 0)
		dup2(fd_cmd[0], STDIN);
	if (fd_cmd[1] != 1)
		dup2(fd_cmd[1], STDOUT);
	else if (i < v->pipe_count)
		dup2(fd_pipe[1], STDOUT);
	if (v->cmd[i] && ft_is_builtin(v->cmd[i]))
		ft_exec_builtin(v, v->cmd[i], v->env);
	else if (v->cmd[i])
	{
		v->process = fork();
		if (v->process == 0)
		{
			close(fd_pipe[0]);
			ft_exec_cmd(v, v->cmd[i], ft_lst_to_strtab(v->cmd[i]),
				ft_lst_to_strtab(v->env));
		}
	}
	close(fd_pipe[1]);
	dup2(std_save[0], STDIN);
	dup2(std_save[1], STDOUT);
	return (fd_pipe[0]);
}

void	ft_finish_execution(t_var *v, int std_save[2])
{
	char	*tmp;
	int		status;

	waitpid(v->process, &status, 0);
	while (wait(NULL) > 0)
		continue ;
	close(std_save[0]);
	close(std_save[1]);
	if (!ft_is_builtin(v->cmd[v->pipe_start - 1]))
	{
		free(v->strings->pipeline_exit_status);
		v->strings->pipeline_exit_status = ft_itoa(ft_get_exit_code(status));
	}
	while (v->cat_exception--)
	{
		if (!tmp[0])
			tmp = readline("\n");
		else
			tmp = readline("");
		if (!v->cat_exception && !tmp[0])
			write(1, "\n", 1);
		free(tmp);
	}
}

void	ft_execution(t_var *v, t_list *fd_cmd)
{
	int	std_save[2];
	int	*fd_cmd_cast;
	int	fd_pipe_out;

	std_save[0] = dup(STDIN);
	std_save[1] = dup(STDOUT);
	ft_cat_exception(v, v->pipe_start + 1, v->pipe_count);
	while (++(v->pipe_start) <= v->pipe_count)
	{
		fd_pipe_out = ft_setup_n_launch(v, std_save,
				(int *)fd_cmd->content, v->pipe_start);
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
	ft_finish_execution(v, std_save);
}
