/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:14:33 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/01 21:08:36 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_sort_env(t_list *env)
{
	t_list	*tmp;
	void	*swp;

	tmp = env;
	while (tmp->next->next)
	{
		if (ft_strcmp(tmp->content, tmp->next->content) > 0)
		{
			swp = tmp->content;
			tmp->content = tmp->next->content;
			tmp->next->content = swp;
			tmp = env;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_export_print(t_list *env)
{
	t_list	*env_cpy;
	t_list	*start;
	char	*tmp;
	int		i;

	env_cpy = ft_lstcpy(env);
	start = env_cpy;
	ft_export_sort_env(env_cpy);
	while (env_cpy->next)
	{
		tmp = (char *)env_cpy->content;
		i = -1;
		ft_putstr_fd("declare -x ", STDOUT);
		while (tmp[++i] != '=')
			ft_putchar_fd(tmp[i], STDOUT);
		ft_putstr_fd("=\"", STDOUT);
		while (tmp[++i])
			ft_putchar_fd(tmp[i], STDOUT);
		ft_putchar_fd('\"', STDOUT);
		ft_putchar_fd('\n', STDOUT);
		env_cpy = env_cpy->next;
	}
	ft_lstfree(&start);
}

int	ft_check_export(t_var *v, char *cmd)
{
	int		i;

	i = -1;
	if (!cmd[0] || cmd[0] == '='
		|| (cmd[1] && !ft_isalpha(cmd[1]) && cmd[1] != '_'))
	{
		if (v)
			ft_builtin_error(v, "export", cmd, "not a valid identifier");
		return (0);
	}
	while (cmd[++i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			if (v)
				ft_builtin_error(v, "export", cmd, "not a valid identifier");
			return (0);
		}
	}
	return (1);
}

void	ft_export_set_var(t_list **env, char *cmd)
{
	t_list	*tmp;
	int		len;

	tmp = *env;
	len = 0;
	while (cmd[len] && cmd[len] != '=')
		++len;
	while (tmp)
	{
		if (!ft_strncmp(cmd, (char *)tmp->content, len))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->content);
		tmp->content = (void *)cmd;
	}
	else
		ft_lstadd_back(env, ft_lstnew(cmd));
}

void	ft_export(t_var *v, t_list *cmd, t_list *env)
{
	char	*var;

	if (!cmd)
		ft_export_print(env);
	while (cmd)
	{
		if (!ft_check_export(v, (char *)cmd->content))
		{
			cmd = cmd->next;
			continue ;
		}
		if (!ft_strchr((char *)cmd->content, '='))
		{
			var = ft_getenv(v->export, (char *)cmd->content);
			if (var)
			{
				var = ft_strjoin_free(ft_strjoin((char *)cmd->content,
							"="), var, 1);
				ft_export_set_var(&env, var);
			}
		}
		else
			ft_export_set_var(&v->export, ft_strdup((char *)cmd->content));
		cmd = cmd->next;
	}
}
