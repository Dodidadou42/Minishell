/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 01:35:48 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/05 19:02:25 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtin(t_list *cmd, t_list *env)
{
	if (!ft_strcmp((char *)cmd->content, "echo"))
		ft_echo(cmd->next);
	else if (!ft_strcmp((char *)cmd->content, "cd"))
		ft_cd(cmd->next, env);
	else if (!ft_strcmp((char *)cmd->content, "pwd"))
		ft_pwd();
	else if (!ft_strcmp((char *)cmd->content, "export"))
		ft_export(cmd->next, env);
	else if (!ft_strcmp((char *)cmd->content, "unset"))
		ft_unset(cmd->next, env);
	else if (!ft_strcmp((char *)cmd->content, "env"))
		ft_env(env);
	else if (!ft_strcmp((char *)cmd->content, "exit"))
	{
		system("leaks minishell");
		exit(0);
	}
	else
		return (0);
	return (1);
}

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
		ft_putstr_fd(cast, STDIN);
		if (cmd->next)
			ft_putchar_fd(' ', STDIN);
		cmd = cmd->next;
	}
	if (nl)
		ft_putchar_fd('\n', STDIN);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	ft_env(t_list *env)
{
	while (env)
	{
		ft_putstr_fd((char *)env->content, STDIN);
		ft_putchar_fd('\n', STDIN);
		env = env->next;
	}
}
