/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 02:11:22 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/11 10:05:04 by mpelazza         ###   ########.fr       */
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
		ft_putstr_fd("declare x ", STDOUT);
		while (tmp[++i] != '=')
			ft_putchar_fd(tmp[i], STDOUT);
		if (tmp[i + 1])
			while (tmp[i])
				ft_putchar_fd(tmp[i++], STDOUT);
		ft_putchar_fd('\n', STDOUT);
		env_cpy = env_cpy->next;
	}
	ft_lstfree(&start);
}

// pas au point les checks je reviendai dessus plus tard

int	ft_check_export(t_var *v, t_list *cmd)
{
	char	*tmp;
	int		i;

	while (cmd)
	{
		tmp = (char *)cmd->content;
		i = -1;
		if (!tmp[0] || tmp[0] == '=')
		{
			ft_builtin_error(v, "export", (char *)cmd->content,
				"not a valid indentifier");
			return (0);
		}
		while (tmp[++i] && tmp[i] != '=')
		{
			if (!ft_isalpha(tmp[i]) && tmp[i] != '_')
			{
				ft_builtin_error(v, "export", (char *)cmd->content,
					"not a valid identifier");
				return (0);
			}
		}
		cmd = cmd->next;
	}
	return (1);
}

void	ft_export(t_var *v, t_list *cmd, t_list *env)
{
	t_list	*tmp;

	if (!cmd)
		ft_export_print(env);
	while (cmd)
	{
		if (!ft_check_export(v, cmd))
			break ;
		if (!ft_strchr((char *)cmd->content, '='))
			cmd->content
				= (void *)ft_strjoin_free((char *)cmd->content, "=", 1);
		tmp = ft_lstlast(env);
		ft_lstadd_back(&env, ft_lstnew((char *)tmp->content));
		tmp->content = (void *)ft_strdup((char *)cmd->content);
		cmd = cmd->next;
	}
}

void	ft_unset(t_list *cmd, t_list *env)
{
	t_list	*prev;
	char	*tmp;
	int		len;

	tmp = ft_strjoin((char *)cmd->content, "=");
	len = ft_strlen(tmp);
	while (env && ft_strncmp(tmp, (char *)env->content, len))
	{
		prev = env;
		env = env->next;
	}
	free(tmp);
	if (env)
	{
		prev->next = prev->next->next;
		free(env->content);
		free(env);
	}
}
