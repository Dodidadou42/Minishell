/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:35:45 by mpelazza          #+#    #+#             */
/*   Updated: 2023/03/22 16:44:19 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_read_command(char *ret, t_var *v)
{
	if (ret)
		free(ret);
	g_sig->pid = -10;
	v->ctrlc.sa_handler = ft_handle_ctrlc;
	sigaction(SIGINT, &v->ctrlc, NULL);
	ret = readline("minishell$> ");
	ft_check_readline(ret, v);
	while (!ret[0])
	{
		free(ret);
		ret = readline("minishell$> ");
		ft_check_readline(ret, v);
	}
	add_history(ret);
	ft_get_history(ret, v);
	return (ret);
}

void	ft_get_env_var(t_list *env, char *line, char *word, int *i[2])
{
	char	*tmp;
	int		len;

	len = ft_env_var_name_len(line);
	if (len < 0)
	{
		*i[0] -= len;
		return ;
	}
	while (env)
	{
		tmp = (char *)env->content;
		if (!ft_strncmp(&line[1], tmp, len) && tmp[len] == '=')
		{
			*i[0] += (len + 1);
			len += 1;
			while (tmp[len])
				word[(*i[1])++] = tmp[len++];
			return ;
		}
		env = env->next;
	}
	*i[0] += (len + 1);
	if (!len)
			word[(*i[1])++] = '$';
}

void	ft_get_quote(t_var *v, char *line, char *word, int *i[2])
{
	char	type;

	type = line[*i[0]];
	if (!ft_strchr(&line[*i[0] + 1], type))
	{
		word[(*i[1])++] = line[(*i[0])++];
		return ;
	}
	line[ft_find_end_quote(&line[*i[0]], *i[0])] = '\0';
	*i[0] += 1;
	while (line[*i[0]])
	{
		if (!ft_strncmp(&line[*i[0]], "$?", 2) && type == '\"')
			ft_pipeline_exit_status(v, word, (int *[]){i[0], i[1]});
		else if (line[*i[0]] == '$' && line[*i[0] + 1]
			&& !ft_iswspace(line[*i[0] + 1]) && type == '\"')
			ft_get_env_var(v->env, &line[*i[0]], word, (int *[]){i[0], i[1]});
		else
			word[(*i[1])++] = line[(*i[0])++];
	}
	line[*i[0]] = type;
	*i[0] += 1;
}

char	*ft_get_word(t_var *v, char *line, int *i, char start)
{
	char	*word;
	int		j;

	word = malloc(ft_word_len(v, v->env, ft_strdup(&line[*i])) + 1);
	j = 0;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			ft_get_quote(v, line, word, (int *[]){i, &j});
		else if (!ft_strncmp(&line[*i], "$?", 2))
			ft_pipeline_exit_status(v, word, (int *[]){i, &j});
		else if (line[*i] == '$' && line[*i + 1]
			&& !ft_iswspace(line[*i + 1]) && start)
			ft_get_env_var(v->env, &line[*i], word, (int *[]){i, &j});
		else if (!ft_strchr(" |<>", line[*i]))
			word[j++] = line[(*i)++];
		else
			break ;
	}
	word[j] = '\0';
	if (!word[0] && start == '$')
		return (ft_free_null(word));
	return (word);
}

t_list	**ft_parse_command(t_var *v)
{
	t_list	**cmd;
	char	*tmp;
	int		i;

	cmd = malloc(sizeof(t_list *)
			* ((ft_count_char(v->strings->line, '|')) + 2));
	cmd[0] = NULL;
	i = 0;
	while (v->strings->line[i])
	{
		while (v->strings->line[i] && ft_iswspace(v->strings->line[i]))
			++i;
		if (v->strings->line[i])
		{
			if (ft_handle_metachar(v, v->strings->line, &i) == 1)
				cmd[++(v->pipe_count)] = NULL;
			else if (v->strings->line[i] && !ft_iswspace(v->strings->line[i]))
			{
				tmp = ft_get_word(v, v->strings->line, &i, v->strings->line[i]);
				if (tmp)
					ft_lstadd_back(&cmd[v->pipe_count], ft_lstnew(tmp));
			}
		}
	}
	return (cmd);
}
