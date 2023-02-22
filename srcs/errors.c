/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:26:37 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/22 15:50:30 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_parsing_error(t_var *v, char *token)
{
	(void)v;
	ft_putstr_fd("-minishell: syntax error near unexpected token `", STDERR);
	ft_putstr_fd(token, STDERR);
	ft_putstr_fd("\'\n", STDERR);
	ft_bzero((void *)v->line, ft_strlen(v->line));
	free(v->pipeline_exit_status);
	v->pipeline_exit_status = ft_itoa(258);
	return (258);
}

int	ft_exec_error(t_var *v, char *cause, char *error, int status)
{
	ft_putstr_fd("-minishell: ", STDERR);
	ft_putstr_fd(cause, STDERR);
	ft_putstr_fd(": ", STDERR);
	if (error)
		ft_putstr_fd(error, STDERR);
	else
		ft_putstr_fd(strerror(errno), STDERR);
	ft_putchar_fd('\n', STDERR);
	free(v->pipeline_exit_status);
	v->pipeline_exit_status = ft_itoa(status);
	return (status);
}

int	ft_builtin_error(t_var *v, char *cmd, char *cause, char *error)
{
	ft_putstr_fd("-minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	if (!ft_strcmp(cmd, "export"))
		ft_putchar_fd('`', STDERR);
	ft_putstr_fd(cause, STDERR);
	if (!ft_strcmp(cmd, "export"))
		ft_putchar_fd('\'', STDERR);
	ft_putstr_fd(": ", STDERR);
	if (error)
		ft_putstr_fd(error, STDERR);
	else
		ft_putstr_fd(strerror(errno), STDERR);
	ft_putchar_fd('\n', STDERR);
	free(v->pipeline_exit_status);
	v->pipeline_exit_status = ft_itoa(1);
	return (1);
}

int	ft_get_exit_code(int status)
{
	if (status == 0)
		return (0);
	else if (status > 0)
		return (status / 256);
	else
	{
		status = -status - 1;
		return (255 - (status / 256));
	}
}
