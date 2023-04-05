/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:49:25 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/22 16:51:33 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_ctrl_slash(int signal)
{	

	(void)signal;
	rl_redisplay();
}

void	do_nothing(int signal)
{
	(void)signal;
}

void	ft_handle_ctrlc(int signal)
{
	(void)signal;
	g_sig->bool_ctrlc = 1;
	if (g_sig->pid < 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_sig->n == 0 && g_sig->pid > 0)
	{
		write(1, "\n", 1);
		kill(g_sig->pid, SIGTERM);
	}
	else if (g_sig->n == 1)
	{
		g_sig->n = 0;
		write(1, "^C\n", 3);
		kill(g_sig->pid, SIGTERM);
	}
}

void	ft_init_signals(t_var *v)
{
	struct termios	new;

	(void)v;
	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &new);
	signal(SIGQUIT, ft_handle_ctrl_slash);
	signal(SIGINT, ft_handle_ctrlc);
}
