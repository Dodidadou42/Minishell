/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:49:25 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/21 21:30:28 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_ctrl_slash(int signal)
{	
	(void)signal;
	rl_redisplay();
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
    ft_change_ctrl_c_function(v, 1);
}