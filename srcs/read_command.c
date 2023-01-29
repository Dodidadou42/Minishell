#include "../includes/minishell.h"

int		check_open_quotes(char	*str)
{
	int	ret;

	ret = 0;
	while (*str)
	{
		if (*str && *str == '\'' && !ret)
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (!*str)
				ret = Q;
		}
		if (*str && *str == '\"' && !ret)
		{
			str++;
			while (*str && *str != '\"')
				str++;
			if (!*str)
				ret = DQ;
		}
		str++;
	}
	return (ret);
}

char	*read_command(void)
{
	char	*ret;
	char	*tmp;

	ret = readline("minishell$> ");
	while (!ft_strlen(ret))
    {
        free(ret);
		ret = readline("minishell$> ");
    }
	while (check_open_quotes(ret))
	{
		if (check_open_quotes(ret) == Q)
		{
			tmp = readline("quote>");
			ret = ft_join_free(ret, tmp);
			free(tmp);
		}
		if (check_open_quotes(ret) == DQ)
		{
			tmp = readline("dquote>");
			ret = ft_join_free(ret, tmp);
			free(tmp);
		}
	}
	return (ret);
}