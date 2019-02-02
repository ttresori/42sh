#include "sh.h"

static void    choice_off(t_42sh *sh, char *to_print_in, char *to_print_out)
{
    sh->stdin->cursor_pos = 17;
    sh->stdin->line_pos = 17;
    sh->prompt_len = 17;
    ft_puts_green("bck-i-search`");
    if (to_print_in)
     {
            ft_puts_yellow(to_print_in);
            sh->stdin->cursor_pos += ft_strlen(to_print_in);
            sh->stdin->line_pos += ft_strlen(to_print_in);
        }
        ft_puts_green("`: ");
        if (to_print_out)
        {
            ft_putstr(to_print_out);
            sh->stdin->cursor_pos += ft_strlen(to_print_out);
            sh->stdin->line_pos += ft_strlen(to_print_out);
        }
        return ;
}

void    print_prompt_search(t_42sh *sh, int choice, char *to_print_in, char *to_print_out, int len_del)
{
     choice == 0 ? (len_del += 17) : (len_del += 25);
    to_print_out == NULL ? (len_del) : (len_del += ft_strlen(to_print_out));
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
        ft_puts_cyan(to_print_in);
        sh->stdin->cursor_pos += ft_strlen(to_print_in);
        sh->stdin->line_pos += ft_strlen(to_print_in);
    }
    ft_puts_green("`: ");
    if (to_print_out)
    {
        sh->stdin->cursor_pos += ft_strlen(to_print_out);
        sh->stdin->line_pos += ft_strlen(to_print_out);
        ft_putstr(to_print_out);
    }
}