/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 02:11:22 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/07 01:00:01 by mpelazza         ###   ########.fr       */
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
		ft_putstr_fd("declare x ", STDIN);
		while (tmp[++i] != '=')
			ft_putchar_fd(tmp[i], STDIN);
		if (tmp[i + 1])
			while (tmp[i])
				ft_putchar_fd(tmp[i++], STDIN);
		ft_putchar_fd('\n', STDIN);
		env_cpy = env_cpy->next;
	}
	ft_lstfree(&start);
}

// pas au point les checks je reviendai dessus plus tard

int	ft_check_export(t_list *cmd)
{
	char	*tmp;

	while (cmd)
	{
		if (!ft_strcmp((char *)cmd->content, "="))
		{
			ft_put_errors("export: ", "=", "not a valid identifier", 0);
			return (0);
		}
		tmp = (char *)cmd->content;
		while (*tmp && *tmp != '=')
			if (ft_isdigit(*tmp++))
				ft_put_errors("export: ", (char *)cmd->content,
					"not a valid identifier", 0);
		cmd = cmd->next;
	}
	return (1);
}

void	ft_export(t_list *cmd, t_list *env)
{
	t_list	*tmp;

	if (!cmd)
		ft_export_print(env);
	while (cmd)
	{
		if (!ft_check_export(cmd))
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
