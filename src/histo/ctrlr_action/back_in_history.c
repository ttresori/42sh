#include "sh.h"

void    print_all_value(t_42sh *sh, char *dup)
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
    ft_puts_blue("sh->pos_arg ");
    ft_putnbr(sh->history_mark->pos_arg);
    ft_putchar('\n');
    ft_puts_blue("character on cursos ");
    ft_putchar(dup[sh->stdin->line_pos]);
    ft_putchar('\n');
}

void    place_curs_before(t_42sh *sh, char *arg, char *dup, int stop)
{
    int i;
    int real_return;

    i = 0;
    real_return = 0;
    while (i < stop)
    {
        if (arg[0] == dup[i])
            if (check_after(arg, dup, 0, i, sh->history_mark->pos_arg - 2))
                    real_return = i;
        i++;
    }
    ft_putchar('\n');
    ft_putnbr(real_return);
    ft_putchar('\n');
    real_return = real_return - sh->stdin->len_line;
    sh->stdin->len_line = ft_strlen(dup);
    sh->stdin->line_pos -= real_return;
    sh->stdin->cursor_pos = sh->prompt_len + sh->stdin->len_line - real_return;
    while(real_return-- > 0)
     tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
}

void    back_in_history(t_42sh *sh, char *dup, char *arg)
{
    print_all_value(sh, dup);
    //sh->history_mark->move_curs = 1;
}