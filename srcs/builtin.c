/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:35:48 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/22 00:08:11 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo_check_opt(char *opt)
{
	int	i;

	if (opt[0] != '-' || !opt[1])
		return (0);
	i = 1;
	while (opt[i] && opt[i] == 'n')
		++i;
	if (!opt[i])
		return (1);
	return (0);
}

void	ft_echo(t_list *cmd)
{
	char	*cast;
	int		nl;

	while (cmd)
	{
		cast = (char *)cmd->content;
		if (ft_echo_check_opt(cast))
		{
			nl = 0;
			cmd = cmd->next;
		}
		else
			break ;
	}
	while (cmd)
	{
		cast = (char *)cmd->content;
		ft_putstr_fd(cast, STDOUT);
		if (cmd->next)
			ft_putchar_fd(' ', STDOUT);
		cmd = cmd->next;
	}
	if (nl)
		ft_putchar_fd('\n', STDOUT);
}

void	ft_pwd(t_var *v)
{
	printf("%s\n", v->strings->pwd + 4);
}

void	ft_env(t_list *env)
{
	while (env)
	{
		if (ft_strchr((char *)env->content, '='))
		{
			ft_putstr_fd((char *)env->content, STDOUT);
			ft_putchar_fd('\n', STDOUT);
		}
		env = env->next;
	}
}

void	ft_exit(t_var *v, t_list *cmd)
{
	char	*cast;
	int		i;

	if (!cmd || cmd->next)
	{
		ft_putstr_fd("exit\n", STDOUT);
		if (!cmd)
			exit(ft_atoi(v->strings->pipeline_exit_status));
		ft_exec_error(v, "exit", "too many arguments", 1);
		return ;
	}
	cast = (char *)cmd->content;
	i = -1;
	while (cast[++i])
	{
		if (!(ft_isdigit(cast[i])
				|| ((cast[i] == '-' || cast[i] == '+') && !i)))
		{
			ft_putstr_fd("exit\n", STDOUT);
			ft_builtin_error(v, "exit", cast, "numeric argument required");
			exit(ft_atoi(v->strings->pipeline_exit_status));
		}
	}
	ft_putstr_fd("exit\n", STDOUT);
	exit(ft_atoi(cast));
}
