/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddychus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 02:09:50 by ddychus           #+#    #+#             */
/*   Updated: 2023/02/14 02:09:52 by ddychus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_get_history(char *line, t_var *v)
{
	t_histo	*tmp;
	int		offset;

	offset = 2;
	if (!v->histo)
	{
		v->histo = malloc(sizeof(t_histo));
		v->histo->cmd = ft_strdup(line);
		v->histo->offset = 1;
		v->histo->next = NULL;
	}
	else
	{
		tmp = v->histo;
		while (tmp->next)
		{
			tmp = tmp->next;
			offset++;
		}
		tmp->next = malloc(sizeof(t_histo));
		tmp->next->cmd = ft_strdup(line);
		tmp->next->offset = offset;
		tmp->next->next = NULL;
	}
}

void	ft_print_history(t_histo *histo)
{
	t_histo	*tmp;

	tmp = histo;
	while (tmp)
	{
		if (tmp->offset < 10)
			printf("    %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 100)
			printf("   %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 1000)
			printf("  %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 10000)
			printf(" %d  %s\n", tmp->offset, tmp->cmd);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}

void	ft_print_history_n_lasts(t_var *v, int n)
{
	t_histo	*tmp;
	int		i;

	tmp = v->histo;
	while (tmp->next)
		tmp = tmp->next;
	i = tmp->offset;
	if (n > i)
		ft_print_history(v->histo);
	tmp = v->histo;
	while (tmp && tmp->offset != i - n + 1)
		tmp = tmp->next;
	if (!tmp)
		return ;
	else
		ft_print_history(tmp);
}

void	ft_print_reverse_history(t_var *v, int n)
{
	int		i;
	t_histo	*tmp;

	tmp = v->histo;
	while (tmp->next)
		tmp = tmp->next;
	i = tmp->offset + 1;
	if (n == -1)
		n = i;
	while (--i > 0 && n)
	{
		tmp = v->histo;
		while (tmp->offset != i)
			tmp = tmp->next;
		if (tmp->offset < 10)
			printf("    %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 100)
			printf("   %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 1000)
			printf("  %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 10000)
			printf(" %d  %s\n", tmp->offset, tmp->cmd);
		n--;
	}
}
