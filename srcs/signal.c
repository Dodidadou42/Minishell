/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:49:25 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/15 19:39:48 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_ctrl_slash(int signal)
{	
	(void)signal;
	rl_redisplay();
}

void	ft_handle_ctrl_c(int signal)
{	
	int	tmp;

	(void)signal;
	tmp = 0;
	if (wait(NULL) > 0)
	{
		tmp = 1;
		write(1, "^C", 2);
	}
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (!tmp)
		rl_redisplay();
}

void	ft_handle_ctrl_c_heredoc(int signal)
{	
	(void)signal;
	wait(NULL);
	write(1, "\n", 1);
	exit(1);
}

void	do_nothing(int signal)
{
	(void)signal;
}

void	ft_init_signals(t_var *v)
{
	struct termios	new;

	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &new);
	signal(SIGQUIT, ft_handle_ctrl_slash);
	sigemptyset(&v->ctrlc.sa_mask);
	v->ctrlc.sa_flags = 0;
	v->ctrlc.sa_handler = ft_handle_ctrl_c;
	sigaction(SIGINT, &v->ctrlc, NULL);
}
