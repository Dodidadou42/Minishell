/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:04:35 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/27 22:55:01 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_set_fd_cmd(void)
{
	t_list	*fd_cmd;
	int		*cast;

	fd_cmd = ft_lstnew(malloc(sizeof(int) * 2));
	cast = (int *)fd_cmd->content;
	cast[0] = STDIN;
	cast[1] = STDOUT;
	return (fd_cmd);
}

void	ft_close_fd_cmd(t_list *fd_cmd)
{
	int	*fd;

	while (fd_cmd)
	{
		fd = (int *)fd_cmd->content;
		if (fd[0] != 0)
			close(fd[0]);
		if (fd[1] != 1)
			close(fd[1]);
		fd_cmd = fd_cmd->next;
	}
}

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
	return (NULL);
}

int	ft_pipeline_exit_status(t_var *v, char *word, int *i[2])
{
	int	j;

	*i[0] += 2;
	if (!word)
		return (ft_strlen(v->pipeline_exit_status));
	j = 0;
	while (v->pipeline_exit_status[j])
		word[(*i[1])++] = v->pipeline_exit_status[j++];
	return (0);
}
