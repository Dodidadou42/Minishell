/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelazza <mpelazza@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:40:22 by mpelazzas         #+#    #+#             */
/*   Updated: 2023/01/27 16:05:55 by mpelazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(t_var *v, t_cmd *cmd)
{
	(void)v;
	(void)cmd;
	//pipes et redirections a gerer ici
	//fonction is_builtin() pour check ou envoyer la commande


}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_var	*v;

	v = NULL;
	v = init_var(v, env);
	
	while(1)
	{
	   v->line = read_command();
	   v->pid_main = fork();
	   if (v->pid_main == 0)
	   {
			v->cmd_untrimmed = parse_command(v->line); // commande avec espaces pour echo
			v->cmd = trim_command(v->cmd_untrimmed); //commande sans les espaces
			printf("trimmed : \n");
			print_cmd(v->cmd);
			printf("untrimmed : \n");
			print_cmd(v->cmd_untrimmed);
			//lexer(v, v->cmd);
			exit(0);
	   }
	   else
	   {
			waitpid(v->pid_main, NULL, 0);
			free(v->line);
			//free_var(v); //je comprends pas pourquoi il segfault lui
			//system("leaks a.out");
			//ya un seul leak c'est v->paths et j'arrive pas a le regler
	   }
	}
}