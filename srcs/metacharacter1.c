/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacter1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:45:18 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/08 02:31:23 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_pipe(t_var *v, char *line, int *i)
{
	int	j;

	j = 0;
	while (j && line[j] == ' ')
		if (line[j++] == '|')
			ft_put_errors("syntax error near unexpected token ", "|", "", 1);
	*i += 1;
	while (line[*i] && line[*i] == ' ')
		++(*i);
	if (!line[*i])
		v->line = ft_strjoin_free(v->line, readline("> "), 3);
	else if (line[*i] == '|')
		ft_put_errors("syntax error near unexpected token ", "|", "", 1);
	ft_lstadd_back(&v->fd_cmd, ft_set_fd_cmd());
}

// peut etre faut dup2(fd_pipe[0], fd_cast[0]); dans le heredoc
void	ft_heredoc(t_var *v, char *line, int *i)
{
	t_list	*tmp1;
	char	*limiter;
	char	*tmp2;
	int		*fd_cast;
	int		fd_pipe[2];

	*i += 2;
	while (line[*i] && line[*i] == ' ')
		++(*i);
	limiter = ft_strjoin_free(ft_get_word(v, line, i), "\n", 1);
	tmp2 = ft_strjoin_free(readline("> "), "\n", 1);
	pipe(fd_pipe);
	while (ft_strcmp(tmp2, limiter))
	{
		ft_putstr_fd(tmp2, fd_pipe[1]);
		free(tmp2);
		tmp2 = ft_strjoin_free(readline("> "), "\n", 1);
	}
	close(fd_pipe[1]);
	free(tmp2);
	free(limiter);
	tmp1 = ft_lstlast(v->fd_cmd);
	fd_cast = (int *)tmp1->content;
	fd_cast[0] = fd_pipe[0];
}

void	ft_get_fd_cmd(t_var *v, char *line, int *i)
{
	t_list	*tmp;
	char	*filename;
	char	*metachar;
	int		*fd_cast;

	metachar = ft_get_metachar(line, i);
	while (line[*i] && line[*i] == ' ')
			++(*i);
	if (!line[*i])
		ft_put_errors("syntax error near unexpected token ", "newline", "", 1);
	if (ft_strchr("<>|", line[*i]))
		ft_put_errors("syntax error near unexpected token ",
			ft_get_metachar(line, i), "", 1);
	filename = ft_get_word(v, line, i);
	tmp = ft_lstlast(v->fd_cmd);
	fd_cast = (int *)tmp->content;
	if (!ft_strcmp(metachar, "<"))
		fd_cast[0] = open(filename, O_RDONLY);
	else if (!ft_strcmp(metachar, ">>"))
		fd_cast[1] = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (!ft_strcmp(metachar, ">"))
		fd_cast[1] = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_cast[0] < 0 || fd_cast[1] < 0)
		ft_put_errors(filename, NULL, NULL, 1);
	free(filename);
}

int	ft_handle_metachar(t_var *v, char *line, int *i)
{
	if (line[*i] == '|')
	{
		ft_handle_pipe(v, line, i);
		return (1);
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		ft_heredoc(v, line, i);
		return (2);
	}
	else if (line[*i] == '<' || line[*i] == '>')
	{
		ft_get_fd_cmd(v, line, i);
		return (2);
	}
	return (0);
}
