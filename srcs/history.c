#include "../includes/minishell.h"

void    ft_print_history(t_histo *histo)
{
    t_histo *tmp;

    tmp = histo;
    while (tmp)
    {
		if (tmp->offset < 10)
        	printf("    %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 100)
        	printf("   %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 1000)
        	printf("  %d  %s\n", tmp->offset, tmp->cmd);
		else if (tmp->offset < 10000)
        	printf(" %d  %s\n", tmp->offset, tmp->cmd);
        if (tmp->next)
            tmp = tmp->next;
        else
            break;
    }
}

void    ft_clear_history(t_histo *histo)
{
    t_histo *tmp;

    rl_clear_history();
    tmp = histo;
    while (tmp)
    {
        free(tmp->cmd);
        free(tmp);
        tmp = tmp->next;
    }
    histo = NULL;

}

void    ft_delete_offset(t_var *v, t_list *cmd, t_histo *histo)
{
    t_histo *tmp;

    tmp = histo;
    if (!cmd->next)
        ft_builtin_error(v, "history", cmd->content, "option requires an argument");
    else
    {
        while (tmp && tmp->offset != ft_atoi((char *)cmd->next->content))
            tmp = tmp->next;
        if (!tmp)
            ft_builtin_error(v, "history", cmd->next->content, "history position out of range");
        else
        {
            while(tmp->next)
            {
                free(tmp->cmd);
                tmp->cmd = ft_strdup(tmp->next->cmd);
                tmp = tmp->next;
            }
            free(tmp->cmd);
            free(tmp);
        }
    }
        //EN TRAVAIL
}

void    ft_history(t_var *v, t_histo *histo, t_list *cmd)
{
    char *s;

    s = NULL;
    if (!cmd)
        ft_print_history(histo);
    else
    {
        s = (char *)cmd->content;
        if (!ft_strcmp(s, "-c"))
            ft_clear_history(histo);
        else if (!ft_strcmp(s, "-d"))
            ft_delete_offset(v, cmd, histo);
    }
}

void    ft_get_history(char *line, t_var *v)
{
    t_histo *tmp;
    int     offset;

    offset = 2;
    if (!v->histo)
    {
        v->histo = malloc(sizeof(t_histo));
        v->histo->cmd = ft_strdup(line);
        v->histo->offset = 1;
        v->histo->next = NULL;
    }
    else
    {
        tmp = v->histo;
        while (tmp->next)
        {       
            tmp = tmp->next;
            offset++;
        }
    tmp->next = malloc(sizeof(t_histo));
    tmp->next->cmd = ft_strdup(line);
    tmp->next->offset = offset;
    tmp->next->next = NULL;
    }
}

