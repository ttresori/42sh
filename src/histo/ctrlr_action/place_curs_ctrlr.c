#include "sh.h"

static  int    check_after(char *arg, char *dup, int i, int i2, int len_arg)
{
    int check;

    check = 0;
    while(check < len_arg)
    {
        if (arg[check] == '\0' || dup[i2] == '\0')
            return (-1);
        if (arg[check] != dup[i2])
        {
            return (-1);
        }
        check++;
        i++;
        i2++;
    }
    return (1);
}

static  int    get_first_c_of_occurence(char *arg, char *dup, int len_arg)
{
    int i;
    int i2;

    i = 0;
    i2 = 0;
    while (dup[i2])
    {
        if (arg[i] == dup[i2])
        {
            if (check_after(arg, dup, i, i2, len_arg) == 1)
                return (i2);
        }
        i2++;
    }
    return (-1);
}

void            place_curs_ctrlr(t_42sh *sh, char *arg, char *dup)
{
    int i;
    int nb_to_move;
    int len_dup;

    len_dup = 0;
    i = 0;
    nb_to_move = 0;
    if (!arg || !dup)
    {
        sh->stdin->len_line = 0;
        sh->stdin->cursor_pos = sh->prompt_len;
        sh->stdin->line_pos = 0;
        return ;
    }
    len_dup = ft_strlen(dup);
    if ((nb_to_move = get_first_c_of_occurence(arg, dup, sh->history_mark->pos_arg)) > -1)
    {
        nb_to_move = len_dup - nb_to_move;
        sh->stdin->len_line = len_dup;
        sh->stdin->cursor_pos = (sh->stdin->len_line  - nb_to_move);
        sh->stdin->line_pos = len_dup - nb_to_move;
        while(nb_to_move-- > 0)
            tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
    }
}