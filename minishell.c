#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_var	*v;

	v = init_var(v, env);

	while(1)
	{
	   v->line = readline("prompt> ");
	   v->pid_main = fork();
	   if (v->pid_main == 0)
	   {
		exec(v->line, env);
		exit(0);
	   }
	   else
	   {
	   	waitpid(v->pid_main, NULL, 0);
		free(v->line);
	   }
	
	}
}