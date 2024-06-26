/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:56:29 by mpelazza          #+#    #+#             */
/*   Updated: 2023/04/11 15:34:52 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_init_env(char **envp, t_var *v)
{
	t_list	*env;
	int		i;

	env = NULL;
	if (envp[0])
	{
		i = -1;
		while (envp[++i])
		{
			if (!ft_strncmp(envp[i], "SHLVL=", 6))
				envp[i][6]++;
			ft_lstadd_back(&env, ft_lstnew(ft_strdup(envp[i])));
		}
	}
	else
	{
		v->bool_env = 0;
		ft_lstadd_back(&env, ft_lstnew(ft_strdup
				("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin)")));
		ft_lstadd_back(&env, ft_lstnew(ft_strjoin("PWD=", getcwd(NULL, 0))));
	}
	ft_export_set_var(&env, ft_strdup("SHELL=minishell"));
	ft_export_set_var(&env, ft_strdup("OLDPWD"));
	return (env);
}

t_var	*ft_init_var(char **envp)
{
	t_var	*v;

	g_sig = malloc(sizeof(t_gsig));
	v = malloc(sizeof(t_var));
	v->bool_env = 1;
	v->env = ft_init_env(envp, v);
	v->export = NULL;
	v->path = NULL;
	v->strings = malloc(sizeof(t_strings));
	v->strings->line = NULL;
	v->strings->pipeline_exit_status = ft_itoa(1);
	v->histo = NULL;
	v->strings->pwd = ft_strjoin("PWD=", ft_getenv(v->env, "PWD"));
	v->strings->old_pwd = ft_strjoin("OLDPWD=", ft_getenv(v->env, "OLDPWD"));
	v->strings->root = ft_strjoin("/Users/", ft_getenv(v->env, "USER"));
	ft_init_signals(v);
	return (v);
}

void	ft_free_var(t_var *v)
{
	int	i;

	i = -1;
	while (++i <= v->pipe_count)
		if (v->cmd[i])
			ft_lstfree_content(&v->cmd[i]);
	free(v->cmd);
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
		g_sig->bool_ctrlc = 0;
		v->strings->line = ft_read_command(v->strings->line, v);
		v->fd_cmd = ft_set_fd_cmd();
		v->pipe_start = -1;
		v->pipe_count = 0;
		v->cat_exception = 0;
		v->cmd = ft_parse_command(v);
		free(v->strings->pipeline_exit_status);
		v->strings->pipeline_exit_status = ft_itoa(0);
		if (v->strings->line && v->strings->line[0] && v->cmd[0])
			ft_execution(v);
		ft_free_var(v);
	}
	return (0);
}
