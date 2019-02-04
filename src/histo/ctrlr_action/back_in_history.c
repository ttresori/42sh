#include "sh.h"

void    print_all_value(t_42sh *sh)
{
    ft_putchar('\n');
    ft_puts_blue("sh->stdin->line_pos : ");
    ft_putnbr(sh->stdin->line_pos);
    ft_putchar('\n');
    ft_puts_blue("sh->stdin->len_line : ");
    ft_putnbr(sh->stdin->len_line);
    ft_putchar('\n');
    ft_puts_blue("sh->stdin->cursor_pos : ");
    ft_putnbr(sh->stdin->cursor_pos );
    ft_putchar('\n');
    ft_puts_blue("sh->promt_len; : ");
    ft_putnbr(sh->prompt_len);
    ft_putchar('\n');
}

static  int    get_before_c_of_occurence(t_42sh *sh, char *arg, char *dup, int len_arg, int stop)
{
    int i2;
    int real_return;

    i2 = 0;
    real_return = -1;
   // if (i2 > 0)
        while (i2 < stop)
        {
            if (arg[0] == dup[i2])
            {
                if (check_after(arg, dup, 0, i2, len_arg) == 1)
                    real_return = i2;
            }
            i2++;
        }
    ft_putnbr(real_return);
    ft_putchar('\n');
    return (real_return);
}

void            place_curs_before(t_42sh *sh, char *arg, char *dup)
{
    int i;
    int nb_to_move;
    int len_dup;

    len_dup = 0;
    i = 0;
    nb_to_move = 0;
    len_dup = ft_strlen(dup);
    if ((nb_to_move = get_before_c_of_occurence(sh, arg, dup, sh->history_mark->pos_arg, sh->stdin->line_pos)) > -1)
    {
        nb_to_move = len_dup - nb_to_move;
        sh->stdin->len_line = len_dup;
        sh->stdin->line_pos = len_dup - nb_to_move;
        sh->stdin->cursor_pos = sh->prompt_len + sh->stdin->len_line - nb_to_move;
        while(nb_to_move-- > 0)
            tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
    }
}

void    back_in_history(t_42sh *sh, char *dup, char *arg)
{
    print_all_value(sh);
    sh->history_mark->move_curs = 1;
    place_curs_before(sh, arg, dup);

}