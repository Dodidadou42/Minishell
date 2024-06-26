/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:59:08 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/01 17:37:37 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_end_quote(char *s, int index)
{
	int		i;

	i = 1;
	while (s[i] && s[i] != s[0])
		i++;
	return (i + index);
}

int	ft_env_var_name_len(char *name)
{
	int	i;
	int	swp;
	int	len;

	if (name[1] && (name[1] == '\'' || name[1] == '\"'))
		return (-1);
	else if (name[1] && ft_isdigit(name[1]))
		return (-2);
	i = 1;
	while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
		++i;
	swp = name[i];
	name[i] = '\0';
	len = ft_strlen(name) - 1;
	name[i] = swp;
	return (len);
}

int	ft_env_var_len(t_list *env, char *name, int *i)
{
	char	*tmp;
	int		len;

	len = ft_env_var_name_len(name);
	if (len < 0)
	{
		*i -= len;
		return (0);
	}
	while (env)
	{
		tmp = (char *)env->content;
		if (!ft_strncmp(&name[1], tmp, len) && tmp[len] == '=')
		{
			*i += (len + 1);
			return (ft_strlen(tmp) - (len + 1));
		}
		env = env->next;
	}
	*i += (len + 1);
	if (!len)
		return (1);
	return (0);
}

int	ft_quote_len(t_list *env, char *line, int *i)
{
	char	type;
	int		len;

	type = line[*i];
	if (!ft_strchr(&line[*i + 1], type))
	{
		*i += 1;
		return (1);
	}
	line[ft_find_end_quote(&line[*i], *i)] = '\0';
	*i += 1;
	len = 0;
	while (line[*i])
	{
		if (line[*i] == '$' && line[*i + 1]
			&& !ft_iswspace(line[*i + 1]) && type == '\"')
			len += ft_env_var_len(env, &line[*i], i);
		else
		{
			++(*i);
			++len;
		}
	}
	*i += 1;
	return (len);
}

int	ft_word_len(t_var *v, t_list *env, char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			len += ft_quote_len(env, line, &i);
		else if (!ft_strncmp(&line[i], "$?", 2))
			len += ft_pipeline_exit_status(v, NULL, (int *[]){&i, NULL});
		else if (line[i] == '$' && line[i + 1] && !ft_iswspace(line[i + 1]))
			len += ft_env_var_len(env, &line[i], &i);
		else if (!ft_strchr(" |<>", line[i]))
		{
			++(i);
			++len;
		}
		else
			break ;
	}
	free(line);
	return (len);
}
