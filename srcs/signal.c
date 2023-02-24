/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:49:25 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/21 21:30:28 by mpelazza         ###   ########.fr       */
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

void	ft_handle_ctrl_c_heredoc(int signal)
{	
	(void)signal;
	write(1, "\n", 1);
	exit(0);
}

void	ft_handle_ctrl_c_cat(int signal)
{	
	(void)signal;
	write(1, "^C\n", 3);
}

void	do_nothing(int signal)
{
	(void)signal;
}

void	ft_change_ctrl_c_function(t_var *v, int n)
{
	if (n == 1)
		v->ctrlc.sa_handler = ft_handle_ctrl_c;
	else if (n == 2)
		v->ctrlc.sa_handler = ft_handle_ctrl_c_heredoc;
	else if (n == 3)
		v->ctrlc.sa_handler = ft_handle_ctrl_c_cat;
	else if (n == 4)
		v->ctrlc.sa_handler = do_nothing;
	sigaction(SIGINT, &v->ctrlc, NULL);
}
