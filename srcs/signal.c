/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:49:25 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/02 06:51:29 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_ctrl_c(int signal)
{	
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_handle_ctrl_slash(int signal)
{	
	(void)signal;
	rl_redisplay();
}

void	ft_init_signals(void)
{
	struct termios	new;
	struct sigaction ctrl_c;

	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &new);
	//signal(SIGINT, ft_handle_ctrl_c);
	
    ctrl_c.sa_handler = ft_handle_ctrl_c;
    sigemptyset(&ctrl_c.sa_mask);
    ctrl_c.sa_flags = 0;
    sigaction(SIGINT, &ctrl_c, NULL);

	signal(SIGQUIT, ft_handle_ctrl_slash);
}