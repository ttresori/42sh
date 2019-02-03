#include "sh.h"

void    back_in_history(t_42sh *sh, char *dup, char *arg)
{
    int i;

    i = 0;
    sh->history_mark->move_curs = 1;
    ft_putchar('\n');
    ft_putnbr(sh->stdin->cursor_pos);
    ft_putchar('\n');
    while (sh->stdin->cursor_pos > 0)
    {
        if (arg[0] == dup[sh->history_mark->move_curs])
            {
                sh->stdin->len_line = ft_strlen(dup);
                sh->stdin->line_pos -= i;
                sh->stdin->cursor_pos = sh->stdin->len_line - i;
                return ;
            }
        sh->stdin->cursor_pos--;
        i++;
    }
}