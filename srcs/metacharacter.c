/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:45:18 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/21 21:24:35 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_handle_pipe(t_var *v, char *line, int *i)
{
	int	j;

	j = 0;
	while (line[j] && ft_iswspace(line[j]))
		++j;
	if (line[j] == '|')
		return (ft_parsing_error(v, "|"));
	*i += 1;
	while (line[*i] && ft_iswspace(line[*i]))
		++(*i);
	if (!line[*i])
		v->line = ft_strjoin_free(v->line, readline("> "), 3);
	else if (line[*i] == '|')
		return (ft_parsing_error(v, "|"));
	ft_lstadd_back(&v->fd_cmd, ft_set_fd_cmd());
	return (1);
}

void	child_heredoc(t_var *v, char *limiter, int fd_cmd[2], int fd_pipe[2])
{
	char	*tmp;

	ft_change_ctrl_c_function(v, 2);
	if (!get_next_line_heredoc(&tmp))
	{
		close(fd_pipe[1]);
		free(limiter);
		fd_cmd[0] = fd_pipe[0];
		return ;
	}
	pipe(fd_pipe);
	while (ft_strcmp(tmp, limiter))
	{
		ft_putstr_fd(tmp, fd_pipe[1]);
		if (!get_next_line_heredoc(&tmp))
			break ;
	}
	close(fd_pipe[1]);
	free(limiter);
	fd_cmd[0] = fd_pipe[0];
}

void	ft_heredoc(t_var *v, int fd_cmd[2], char *line, int *i)
{
	char	*limiter;
	int		fd_pipe[2];
	int		pid;

	*i += 2;
	while (line[*i] && ft_iswspace(line[*i]))
		++(*i);
	limiter = ft_strjoin_free(ft_get_word(v, line, i), "\n", 1);
	pid = fork();
	if (pid == 0)
	{
		child_heredoc(v, limiter, fd_cmd, fd_pipe);
		exit(0);
	}
	else
	{
		ft_change_ctrl_c_function(v, 4);
		waitpid(pid, NULL, 0);
		ft_change_ctrl_c_function(v, 1);
		free(limiter);
	}
}

int	ft_get_fd_cmd(t_var *v, int fd_cmd[2], char *line, int *i)
{
	char	*filename;
	char	*metachar;

	metachar = ft_get_metachar(line, i);
	while (line[*i] && ft_iswspace(line[*i]))
			++(*i);
	if (!line[*i])
		return (ft_parsing_error(v, "newline"));
	if (ft_strchr("<>|", line[*i]))
		return (ft_parsing_error(v, ft_get_metachar(line, i)));
	filename = ft_get_word(v, line, i);
	if (!ft_strcmp(metachar, "<"))
		fd_cmd[0] = open(filename, O_RDONLY);
	else if (!ft_strcmp(metachar, ">>"))
		fd_cmd[1] = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (!ft_strcmp(metachar, ">"))
		fd_cmd[1] = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_cmd[0] < 0 || fd_cmd[1] < 0)
	{
		ft_exec_error(v, filename, NULL, 1);
		v->pipe_start = v->pipe_count;
	}
	free(filename);
	return (0);
}

int	ft_handle_metachar(t_var *v, char *line, int *i)
{
	if (line[*i] == '|')
		return (ft_handle_pipe(v, line, i));
	if (line[*i] == '<' && line[*i + 1] == '<')
		ft_heredoc(v, (int *)ft_lstlast(v->fd_cmd)->content, line, i);
	else if (line[*i] == '<' || line[*i] == '>')
		ft_get_fd_cmd(v, (int *)ft_lstlast(v->fd_cmd)->content, line, i);
	return (0);
}
