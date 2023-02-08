/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:35:45 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/07 19:57:29 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_read_command(char *ret)
{
	if (ret)
		free(ret);
	ret = readline("minishell$> ");
	while (!ret[0])
	{
		free(ret);
		ret = readline("minishell$> ");
	}
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
		if (line[*i[0]] == '$' && type == '\"')
			ft_get_env_var(env, &line[*i[0]], word, (int *[]){i[0], i[1]});
		else
			word[(*i[1])++] = line[(*i[0])++];
	}
	*i[0] += 1;
}

char	*ft_get_word(t_var *v, char *line, int *i)
{
	char	*word;
	int		j;

	j = ft_handle_metachar(v, line, i);
	if (j == 1)
		return (NULL);
	if (j == 2)
		return ("");
	word = malloc(sizeof(char) * (ft_word_len(v->env,
					ft_strdup(&line[*i])) + 1));
	j = 0;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			ft_get_quote(v->env, line, word, (int *[]){i, &j});
		else if (line[*i] == '$')
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
	char	*tmp;
	int		i;
	int		j;

	cmd = malloc(sizeof(t_list *) * ((ft_count_char(v->line, '|')) + 2));
	cmd[0] = NULL;
	i = 0;
	j = 0;
	while (v->line[i])
	{
		while (v->line[i] && v->line[i] == ' ')
			++i;
		if (v->line[i])
		{
			tmp = ft_get_word(v, v->line, &i);
			if (tmp && tmp[0])
				ft_lstadd_back(&cmd[j], ft_lstnew(tmp));
			else if (!tmp)
				cmd[++j] = NULL;
		}
	}
	cmd[++j] = NULL;
	return (cmd);
}
