/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:42:48 by mpelazzas         #+#    #+#             */
/*   Updated: 2023/01/27 16:05:56 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, (str + i), 1);
}

void	ft_put_errors(char *cause, char *details, int is_exit)
{
	write(ERROR, "minishell: ", 7);
	ft_putstr_fd(cause, ERROR);
	write(ERROR, ": ", 2);
	if (details)
		ft_putstr_fd(details, ERROR);
	else
		ft_putstr_fd(strerror(errno), ERROR);
	write(ERROR, "\n", 1);
	if (is_exit)
		exit(is_exit);
}

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}
