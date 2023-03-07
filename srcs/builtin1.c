/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:35:48 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/21 21:50:02 by mpelazza         ###   ########.fr       */
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
		ft_putstr_fd((char *)env->content, STDOUT);
		ft_putchar_fd('\n', STDOUT);
		env = env->next;
	}
}

void	ft_unset(t_list *cmd, t_list *env)
{
	t_list	*prev;
	char	*tmp;
	int		len;

	tmp = ft_strjoin((char *)cmd->content, "=");
	len = ft_strlen(tmp);
	while (env && ft_strncmp(tmp, (char *)env->content, len))
	{
		prev = env;
		env = env->next;
	}
	free(tmp);
	if (env)
	{
		prev->next = prev->next->next;
		free(env->content);
		free(env);
	}
}
