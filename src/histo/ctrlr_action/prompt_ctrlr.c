#include "sh.h"

static void    choice_off(t_42sh *sh, char *to_print_in, char *to_print_out)
{
    int len_in;
    int len_out;

    len_in = 0;
    len_out = 0;
    sh->stdin->cursor_pos = 16;
    sh->stdin->line_pos = 16;
    sh->prompt_len = 16;
    ft_puts_green("bck-i-search`");
    if (to_print_in)
     {
        len_in = sh->history_mark->pos_arg;
        ft_puts_yellow(to_print_in);
        sh->stdin->cursor_pos += len_in;
        sh->stdin->line_pos += len_in;
        sh->prompt_len += len_in;
    }
    ft_puts_green("`: ");
    if (to_print_out)
    {
        len_out = ft_strlen(to_print_out);
        ft_putstr(to_print_out);
        sh->stdin->line_pos += len_out;
        sh->stdin->cursor_pos += len_out;
    }
    return ;
}

void    print_prompt_search(t_42sh *sh, int choice, char *to_print_in, char *to_print_out, int len_del)
{
    int len_in;
    int len_out;

    len_in = 0;
    len_out = 0;
    len_del = sh->stdin->len_line + sh->prompt_len;
    clean_line_lentoback(len_del);
    if (choice == 0)
    {
       choice_off(sh, to_print_in, to_print_out);
       return ;
    }
    sh->stdin->cursor_pos = 25;
    sh->stdin->line_pos = 25;
    sh->prompt_len = 25;
    ft_puts_green("failing bck-i-search`");
    if (to_print_in)
    {
        len_in = ft_strlen(to_print_in);
        ft_puts_cyan(to_print_in);
        sh->stdin->cursor_pos += len_in;
        sh->stdin->line_pos += len_in;
        sh->prompt_len += len_in;
    }
    ft_puts_green("`: ");
    if (to_print_out)
    {
        len_out = ft_strlen(to_print_out);
        sh->stdin->cursor_pos += len_out;
        sh->stdin->line_pos += len_out;
        ft_putstr(to_print_out);
    }
}