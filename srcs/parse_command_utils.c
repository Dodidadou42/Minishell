#include "../includes/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->s)
			printf("%s\n", tmp->s);
		if (tmp->next)
			tmp = tmp->next;
		else
			break;
		}
}

t_cmd	*trim_command(t_cmd *command)
{
	t_cmd	*ret;
	t_cmd	**ret_current;
	t_cmd	*cmd;

	ret = NULL;
	ret_current = &ret;
	cmd = command;
	while(cmd)
	{
		if (ft_strcmp(cmd->s, " "))
		{
			*ret_current = malloc(sizeof(t_cmd));
			(*ret_current)->s = ft_strdup(cmd->s);
			(*ret_current)->type = cmd->type;
			(*ret_current)->next = NULL;
			ret_current = &(*ret_current)->next;
		}
		cmd = cmd->next;
	}
	return (ret);
}

t_cmd	*add_cmd(int n)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (0);
	if (!n)
	{
		ret->s = ft_strdup(" ");
		ret->type = SP;
	}
	else
		ret->s = NULL;
	ret->next = NULL;
	return (ret);
}

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
        return 1;
    return 0;
}

int	get_wordlen(char *line, int type)
{
	int	i;
	char	*l;

	l = line;
	i = 0;
	if (type == SP)
	{
		while (!is_space(l[i]) && l[i] != '\'' && l[i] != '\"' && l[i])
			i++;
	}
	else if (type == DQ)
	{
		l++;
		while (l[i] && l[i] != '\"')
			i++;
	}
	else if (type == Q)
	{
		l++;
		while (l[i] && l[i] != '\'')
			i++;
	}
	return (i);
}

