/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:04:35 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/10 00:50:31 by mpelazza         ###   ########.fr       */
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

int	get_next_line_heredoc(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	write(1, "> ", 2);
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}