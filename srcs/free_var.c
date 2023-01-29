#include "../includes/minishell.h"

void    free_double_tab(char **tab)
{
    int i;

    i = -1;
    while (tab[++i])
        free(tab[i]);
    free(tab);
}

void    free_var(t_var *v)
{
    free_double_tab(v->paths);
}