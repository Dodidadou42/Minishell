/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:35:45 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/11 10:20:58 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_read_command(char *ret, t_var *v)
{
	if (ret)
		free(ret);
	ret = readline("minishell$> ");

	while (!ret[0])
	{
		free(ret);
		ret = readline("minishell$> ");
	}
	add_history(ret);
	ft_get_history(ret, v);
	return (ret);
}

void	ft_get_env_var(t_list *env, char *line, char *word, int *i[2])
{
	char	*tmp;
	int		len;
	int		j;

	len = ft_env_var_name_len(line);
	while (env)
	{
		tmp = (char *)env->content;
		if (!ft_strncmp(&line[1], tmp, len) && tmp[len] == '=')
		{
			j = len + 1;
			while (tmp[j])
				word[(*i[1])++] = tmp[j++];
			*i[0] += (len + 1);
			return ;
		}
		env = env->next;
	}
	*i[0] += (len + 1);
}

void	ft_get_quote(t_list *env, char *line, char *word, int *i[2])
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
		if (line[*i[0]] == '$' && line[*i[0] + 1]
			&& !ft_iswspace(line[*i[0] + 1]) && type == '\"')
			ft_get_env_var(env, &line[*i[0]], word, (int *[]){i[0], i[1]});
		else
			word[(*i[1])++] = line[(*i[0])++];
	}
	line[*i[0]] = type;
	*i[0] += 1;
}

char	*ft_get_word(t_var *v, char *line, int *i)
{
	char	*word;
	int		j;

	word = malloc(sizeof(char) * (ft_word_len(v->env,
					ft_strdup(&line[*i])) + 1));
	j = 0;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			ft_get_quote(v->env, line, word, (int *[]){i, &j});
		else if (line[*i] == '$' && line[*i + 1] && !ft_iswspace(line[*i + 1]))
			ft_get_env_var(v->env, &line[*i], word, (int *[]){i, &j});
		else if (!ft_strchr(" |<>", line[*i]))
			word[j++] = line[(*i)++];
		else
			break ;
	}
	word[j] = '\0';
	return (word);
}

t_list	**ft_parse_command(t_var *v)
{
	t_list	**cmd;
	int		i;

	cmd = malloc(sizeof(t_list *) * ((ft_count_char(v->line, '|')) + 2));
	cmd[0] = NULL;
	i = 0;
	while (v->line[i])
	{
		while (v->line[i] && ft_iswspace(v->line[i]))
			++i;
		if (v->line[i])
		{
			if (ft_handle_metachar(v, v->line, &i) == 1)
				cmd[++(v->pipe_count)] = NULL;
			else if (v->line[i] && !ft_iswspace(v->line[i]))
				ft_lstadd_back(&cmd[v->pipe_count],
					ft_lstnew(ft_get_word(v, v->line, &i)));
		}
	}
	return (cmd);
}
