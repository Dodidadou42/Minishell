#include "../includes/minishell.h"

int	get_word_sp(char	*l, t_cmd	*tmp)
{
	int		len;
	int		i;

	len = get_wordlen(l, SP);
	tmp->s = malloc(sizeof(char) * (len + 1));
	tmp->type = SP;
	

	i = -1;
	while (!is_space(l[++i]) && l[i] != '\'' && l[i] != '\"' && l[i])
			tmp->s[i] = l[i];
		tmp->s[i] = 0;

	return (len);
}

int	get_word_dq(char	*l, t_cmd	*tmp)
{
	int		len;
	int		i;

	len = get_wordlen(l, DQ);
	tmp->s = malloc(sizeof(char) * (len + 1));
	len += 2;
	tmp->type = DQ;

	l++;
	i = -1;
	while (l[++i] && l[i] != '\"')
		tmp->s[i] = l[i];
	tmp->s[i] = 0;
	return (len);
}

int	get_word_q(char	*l, t_cmd	*tmp)
{
	int		len;
	int		i;

	len = get_wordlen(l, Q);
	tmp->s = malloc(sizeof(char) * (len + 1));
	len += 2;
	tmp->type = Q;

	l++;
	i = -1;
	while (l[++i] && l[i] != '\'')
		tmp->s[i] = l[i];
	tmp->s[i] = 0;
	return (len);
}

void	manage_space(char **line, t_cmd **tmp)
{
	if (*line[0] && is_space(*line[0]))
		{
			tmp[0]->next = add_cmd(SP);
			tmp[0] = tmp[0]->next;
			line[0]++;
		}
		if (*line[0])
		{
			tmp[0]->next = add_cmd(1);
			tmp[0] = tmp[0]->next;
		}
}

t_cmd	*parse_command(char *line)
{
	t_cmd	*ret;
	t_cmd	*tmp;
	int		len;

	ret = malloc(sizeof(t_cmd));
	tmp = ret;
	while (*line)
	{
		tmp->type = SP;
		while (is_space(*line) && *line)
			line++;
		if (*line == 0)
			break;
		if (*line == '\"')
			len = get_word_dq(line, tmp);
		else if (*line == '\'')
			len = get_word_q(line, tmp);
		else
			len = get_word_sp(line, tmp);
		line += len;
		manage_space(&line, &tmp);
	}

	return (ret);
}