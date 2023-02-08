/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:56:29 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/08 23:06:48 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_var	*ft_init_var(char **envp)
{
	t_var	*v;
	int		i;

	if (!envp[0])
	{
		envp[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
		envp[1] = NULL;
	}
	v = malloc(sizeof(t_var));
	v->env = NULL;
	i = -1;
	while (envp[++i])
		ft_lstadd_back(&v->env, ft_lstnew(ft_strdup(envp[i])));
	v->path = NULL;
	v->line = NULL;
	return (v);
}

void	ft_free_var(t_var *v)
{
	int	i;

	i = -1;
	while (++i < v->pipe_count)
		if (v->cmd[i])
			ft_lstfree_content(&v->cmd[i]);
	free(v->cmd);
	ft_close_fd_cmd(v->fd_cmd);
	ft_lstfree_content(&v->fd_cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*v;

	(void)argc;
	(void)argv;
	v = ft_init_var(envp);
	while (1)
	{
		v->line = ft_read_command(v->line);
		v->fd_cmd = ft_set_fd_cmd();
		v->cmd = ft_parse_command(v);
		ft_execution(v, v->fd_cmd);
		ft_free_var(v);
	}
	return (0);
}

// signal c'est pour intercepter les ctrl-* mais ca marche pas encore
//	signal(SIGINT, ft_sig_handler);

	/*//printage commande////////////////////////////////////////////////////
		t_list	*tmp;
		for (i = 0; i < v->pipe_count; i++)
		{	
			printf("pipe[%d]:\n", i);	
			if (v->cmd[i])
			{
				tmp = v->cmd[i];
				while (tmp)
				{
					printf("> %s$\n", (char *)tmp->content);
					tmp = tmp->next;
				}
			}
		}
		//printage fd
		i = 0;
		tmp = v->fd_cmd;
		while (tmp)
		{
			int *fdd = (int *)tmp->content;
			printf("%d: fd[0] = %d\tfd[1] = %d\n", i++, fdd[0], fdd[1]);
			tmp = tmp->next;
		}//////////////////////////////////////////////////////////////////*/