/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 22:56:20 by mpelazza          #+#    #+#             */
/*   Updated: 2023/02/07 01:02:23 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../includes/minishell.h"


// Il faut chercher le path dans l'env a chaque commande a la place 
	de le faire qu'au debut au cas ou le correcteur fait 
	export "PATH=Bonjour | cat text.txt" par exemple

char	*ft_get_path(char *cmd, char **paths)
{	
	char	*tmp;
	int		i;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin_free(paths[i], ft_strjoin("/", cmd), 2);
		if (!access(tmp, F_OK))
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

// comme c'est des listes faut retransformer le tout en tableau
// pour l'env je suis pas sur mais je me dit si qq s'amuse a unset 
// le PATH pendant la correction il verra que ca change rien 
// si on met juste le char ** et on peux se faire bz

void	ft_exec_cmd(t_var *v)
{
	char	**args;
	char	**envp;
	char	*path;

	args = ft_list_to_string_tab(v->cmd);
	envp = ft_list_to_string_tab(v->env);
	path = ft_get_path((char *)v->cmd->content, v->path);
	if (!path)
	{
		ft_split_free(args);
		ft_split_free(envp);
		ft_put_errors((char *)v->cmd->content, "command not found", 127);
	}
	execve(path, args, envp);
	ft_split_free(args);
	ft_split_free(envp);
	ft_put_errors((char *)v->cmd->content, "permission denied", 126);
}
*/
/*void	ft_process_cmd(t_var *v) Faut faire les forks avec les pipes tout ca
{
	
}*/