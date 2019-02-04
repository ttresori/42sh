#include "fc.h"

int   check_if_digit(t_42sh *sh)
{
        if ((ft_isdigit(sh->argv->argv[2][0]) == 1) && sh->argv->argv[3] == NULL)    // -l 1 NULL
           {
                print_delimit_history(sh, ft_atoi(sh->argv->argv[2]),
                sh->history_mark->size);
                return (1);
           }
        if ((ft_isdigit(sh->argv->argv[2][0]) == 1)   // -l 1 2
        && (ft_isdigit(sh->argv->argv[3][0]) == 1))
        {
            print_delimit_history(sh, ft_atoi(sh->argv->argv[2]),
            ft_atoi(sh->argv->argv[3]));
            return (1);
        }
    return (0);
}

int   check_if_alpha(t_42sh *sh)
{
    if ((ft_isalpha(sh->argv->argv[2][0]) == 1) && sh->argv->argv[3] == NULL)    // -l a  NULL
    {
            //print_delimit_history_str(sh, sh->argv->argv[2]);
            return (1);
    }
    if ((ft_isalpha(sh->argv->argv[2][0]) == 1) // -ls a b
        && (ft_isalpha(sh->argv->argv[3][0]) == 1))
        {
            //print_delimit_history(sh, ft_atoi(sh->argv->argv[2]), ft_atoi(sh->argv->argv[3])); 
            return (1);
        }
    return (0);
}