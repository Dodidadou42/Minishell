/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:18:35 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/07 01:00:13 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_put_errors(char *cause, char *details, char *msg, int is_exit)
{
	ft_putstr_fd("-minishell: ", STDERR);
	if (cause)
		ft_putstr_fd(cause, STDERR);
	if (details)
	{
		ft_putchar_fd('`', STDERR);
		ft_putstr_fd(details, STDERR);
		ft_putchar_fd('\'', STDERR);
	}
	ft_putstr_fd(": ", STDERR);
	if (msg)
		ft_putstr_fd(msg, STDERR);
	else
		ft_putstr_fd(strerror(errno), STDERR);
	write(STDERR, "\n", 1);
	if (is_exit)
		exit(is_exit);
}

char	**ft_list_to_string_tab(t_list *lst)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		tab[i++] = ft_strdup((char *)lst->content);
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_count_char(char *s, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i] == c)
			++count;
	return (count);
}
