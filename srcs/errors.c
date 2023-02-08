/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:26:37 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/08 02:27:37 by mpelazza         ###   ########.fr       */
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
// faire plusieurs fontctions pcq ca va pas 