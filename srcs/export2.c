/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:36:49 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/22 16:53:50 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export_unset(t_var *v, char *cmd)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		++i;
	if (!cmd[i])
		i = 0;
	else
		cmd[i] = '\0';
	tmp = ft_lstnew(ft_strdup((void *)cmd));
	ft_unset(v, tmp, &v->export);
	ft_lstfree_content(&tmp);
	if (i)
		cmd[i] = '=';
}

void	ft_assignation(t_var *v, char *a)
{
	char	*tmp;

	tmp = ft_getenv(v->env, a);
	if (tmp)
		ft_export_set_var(&v->env, ft_strdup(a));
	else
		ft_export_set_var(&v->export, ft_strdup(a));
}

void	ft_setup_export(t_var *v, char *cmd, int len, t_list *export)
{
	char	*cast;

	if (!ft_strchr(cmd, '='))
	{
		if (!ft_getenv(v->export, cmd))
			ft_export_set_var(&v->env, ft_strdup(cmd));
		else
		{
			while (export)
			{
				cast = (char *)export->content;
				if (!ft_strncmp(cast, cmd, len) && cast[len] == '=')
					break ;
				export = export->next;
			}
			ft_export_set_var(&v->env, ft_strdup((char *)export->content));
			ft_export_unset(v, cmd);
		}
	}
	else
	{
		ft_export_set_var(&v->env, ft_strdup(cmd));
		if (ft_getenv(v->export, cmd))
			ft_export_unset(v, cmd);
	}
}

//checker unset	//if '=' dans le unset error
void	ft_setup_unset(t_list **env, t_list *cmd, t_list *prev)
{
	char	*tmp;
	int		len;

	tmp = ft_strjoin((char *)cmd->content, "=");
	len = ft_strlen(tmp);
	while (*env && ft_strncmp(tmp, (char *)(*env)->content, len))
	{
		prev = *env;
		*env = (*env)->next;
	}
	if (*env)
	{
		if (prev)
			prev->next = prev->next->next;
		free((*env)->content);
		free(*env);
		*env = NULL;
	}
	free(tmp);
}

void	ft_unset(t_var *v, t_list *cmd, t_list **env)
{
	while (cmd)
	{
		if (!ft_check_export(v, (char *)cmd->content, "unset"))
		{
			cmd = cmd->next;
			continue ;
		}
		ft_setup_unset(env, cmd, NULL);
		cmd = cmd->next;
	}
}
