/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:18:35 by mpelazza          #+#    #+#             */
/*   Updated: 2023/04/05 04:25:50 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_readline(char *ret, t_var *v)
{
	if (!ret)
	{
		if (v->bool_env)
			printf("\033[Aminishell$> exit\n");
		else
			printf("exit\n");
		exit(0);
	}
}

char	**ft_lst_to_strtab(t_list *lst)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	i = 0;
	while (lst)
	{
		tab[i++] = ft_strdup((char *)lst->content);
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_count_char(char *s, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i] == c)
			++count;
	return (count);
}

char	*ft_getenv(t_list *env, char *name)
{
	char	*cast;
	int		len;

	len = 0;
	while (name[len] && name[len] != '=')
		++len;
	while (env)
	{
		cast = (char *)env->content;
		if (!ft_strncmp(cast, name, len))
		{	
			if (!cast[len])
				return ("");
			else if (cast[len] == '=')
				return (&cast[len + 1]);
		}
		env = env->next;
	}
	return (NULL);
}

t_list	*ft_set_fd_cmd(void)
{
	t_list	*fd_cmd;
	int		*cast;

	fd_cmd = ft_lstnew(malloc(sizeof(int) * 2));
	cast = (int *)fd_cmd->content;
	cast[0] = STDIN;
	cast[1] = STDOUT;
	return (fd_cmd);
}
