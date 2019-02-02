#include "sh.h"

void       get_new_line_ctrlr(t_42sh *sh, int i, char *dup)
{
        get_substitute(sh, i, dup, 0);
        sh->stdin->len_line = ft_strlen(dup);
        sh->stdin->cursor_pos = sh->stdin->len_line + sh->prompt_len;
        //ft_putnbr(sh->stdin->cursor_pos);
        sh->stdin->line_pos += ft_strlen(dup);
}


void    clean_line_lentoback(int len_to_left)
{

    while (len_to_left >= 0)
    {
        tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
        len_to_left--;
    }
    tputs(tgetstr("dl", NULL), 0, putchar_custom);
}

static int check_following(char *to_find, char *search, int len_check, int start_search)
{
    int i;

    i = 0;
    while(len_check >= 0)
    {
        if (to_find[i] != search[start_search++])
            return (-1);
        len_check--;
        i++;
    }
    return (1);
}

int         is_in_str(char *to_find, char *search, int len_check)
{
    int i;

    i = 0;
    while (search[i])
    {
        if (search[i] == to_find[0])
            if (check_following(to_find, search, len_check, i) == 1)
                return (0);
       i++;
    }
    return (-1);
}