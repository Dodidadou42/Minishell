/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 02:09:43 by ddychus           #+#    #+#             */
/*   Updated: 2023/02/14 02:09:45 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_history(t_histo *histo);
void	ft_print_reverse_history(t_var *v, int n);
void	ft_print_history_n_lasts(t_var *v, int n);

void	ft_clear_history(t_var *v)
{
	t_histo	*tmp;

	rl_clear_history();
	tmp = v->histo;
	while (tmp)
	{
		free(tmp->cmd);
		free(tmp);
		tmp = tmp->next;
	}
	v->histo = NULL;
}

void	ft_delete_offset_next(t_histo *tmp, t_histo *tmplast, t_var *v)
{
	t_histo	*del;
	int		i;

	i = 0;
	if (tmplast && tmp->next)
		tmplast->next = tmp->next;
	else if (tmplast && !tmp->next)
		tmplast->next = NULL;
	else if (!tmplast)
		v->histo = tmp->next;
	del = v->histo;
	while (del)
	{
		del->offset = ++i;
		del = del->next;
	}
	free(tmp->cmd);
	free(tmp);
}

void	ft_delete_offset(t_var *v, t_list *cmd)
{
	t_histo	*tmp;
	t_histo	*tmplast;

	tmp = v->histo;
	tmplast = NULL;
	if (!cmd->next)
		ft_builtin_error(v, "history", cmd->content,
			"option requires an argument");
	else
	{
		while (tmp && tmp->offset != ft_atoi((char *)cmd->next->content))
		{
			tmplast = tmp;
			tmp = tmp->next;
		}
		if (!tmp)
			ft_builtin_error(v, "history", cmd->next->content,
				"history position out of range");
		else
			ft_delete_offset_next(tmp, tmplast, v);
	}
}

int	check_history_arg(t_var *v, char *arg)
{
	char	*s;
	int		i;

	i = -1;
	s = arg;
	if (*s == '-')
	{
		ft_builtin_error(v, "history", s, "invalid option");
		return (0);
	}
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			ft_builtin_error(v, "history", s, "numeric argument required");
			return (0);
		}
	}
	return (1);
}

void	ft_history(t_var *v, t_list *cmd)
{
	char	*s;

	s = NULL;
	if (!cmd)
		ft_print_history(v->histo);
	else
	{
		s = (char *)cmd->content;
		if (!ft_strcmp(s, "-c"))
			ft_clear_history(v);
		else if (!ft_strcmp(s, "-d"))
			ft_delete_offset(v, cmd);
		else if (!ft_strcmp(s, "-r"))
		{
			if (cmd->next && check_history_arg(v, (char *)cmd->next->content))
				ft_print_reverse_history(v,
					ft_atoi((char *)cmd->next->content));
			else if (!cmd->next)
				ft_print_reverse_history(v, -1);
		}
		else if (check_history_arg(v, s))
			ft_print_history_n_lasts(v, ft_atoi(s));
	}
}
