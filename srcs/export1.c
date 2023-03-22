/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:14:33 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/22 16:49:33 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_sort_env(t_list *env)
{
	t_list	*tmp;
	void	*swp;

	tmp = env;
	while (tmp->next)
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

void	ft_export_print(t_list *env_cpy)
{
	t_list	*start;
	char	*tmp;
	int		i;

	start = env_cpy;
	ft_export_sort_env(env_cpy);
	while (env_cpy)
	{
		tmp = (char *)env_cpy->content;
		ft_putstr_fd("declare -x ", STDOUT);
		i = -1;
		while (tmp[++i] && tmp[i] != '=')
			ft_putchar_fd(tmp[i], STDOUT);
		if (tmp[i])
		{
			ft_putstr_fd("=\"", STDOUT);
			ft_putstr_fd(&tmp[++i], STDOUT);
			ft_putchar_fd('\"', STDOUT);
		}
		ft_putchar_fd('\n', STDOUT);
		env_cpy = env_cpy->next;
	}
	ft_lstfree(&start);
}

int	ft_check_export(t_var *v, char *cmd, char *cmd_name)
{
	int		i;

	i = -1;
	if (!cmd[0] || cmd[0] == '='
		|| (!ft_isalpha(cmd[0]) && cmd[0] != '_'))
	{
		if (v)
			ft_builtin_error(v, cmd_name, cmd, "not a valid identifier");
		return (0);
	}
	while (cmd[++i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			if (v)
				ft_builtin_error(v, cmd_name, cmd, "not a valid identifier");
			return (0);
		}
	}
	return (1);
}

void	ft_export_set_var(t_list **env, char *cmd)
{
	t_list	*tmp;
	char	*cast;
	int		len;

	tmp = *env;
	len = 0;
	while (cmd[len] && cmd[len] != '=')
		++len;
	while (tmp)
	{
		cast = (char *)tmp->content;
		if (!ft_strncmp(cmd, cast, len) && (!cast[len] || cast[len] == '='))
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
	if (!cmd)
		ft_export_print(ft_lstcpy(env));
	while (cmd)
	{
		if (!ft_check_export(v, (char *)cmd->content, "export"))
		{
			cmd = cmd->next;
			continue ;
		}
		ft_setup_export(v, (char *)cmd->content,
			ft_strlen((char *)cmd->content), v->export);
		cmd = cmd->next;
	}
}
