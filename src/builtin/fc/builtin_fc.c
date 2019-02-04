#include "fc.h"

void    print_nb_and_str(int nb, char *str)
{
    ft_putnbr(nb);
    ft_putstr("\t");
    ft_putl_cyan(str);
}

void    print_delimit_history(t_42sh *sh, int start, int stop)
{
    t_history *tmp;
    int i;

    i = 0;
    tmp = sh->history_mark->last;
    while (i < sh->history_mark->size - 1)
    {
        if (i >= start && i <= stop)
            print_nb_and_str(i, tmp->str);
        tmp = tmp->prev;
        i++;
    }
}

void    check_for_l_opt(t_42sh *sh)
{
    if (ft_strcmp(sh->argv->argv[1], "-l") == 0)
    {
        if (sh->argv->argv[2] == NULL)
            print_delimit_history(sh, sh->history_mark->size - 16, sh->history_mark->size);
        else if (sh->argv->argv[2] && sh->argv->argv[3] == NULL)
            print_delimit_history(sh, ft_atoi(sh->argv->argv[2]), sh->history_mark->size);
        else if (sh->argv->argv[2] && sh->argv->argv[3])
            print_delimit_history(sh, ft_atoi(sh->argv->argv[2]), ft_atoi(sh->argv->argv[3]));
    }
}

void    builtin_fc(t_42sh *sh)
{
    check_for_l_opt(sh);
}