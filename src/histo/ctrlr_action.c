#include "sh.h"

static char *search_history_ctrl_r(t_42sh *sh, char *to_find, int len_str_to_find)
{
    char        *sub;
    int         size_list;
    t_history   *tmp;

    sub = NULL;
    tmp = NULL;
    tmp = sh->history_mark->begin;
    size_list = sh->history_mark->size;
    while (size_list > 0)
    {
        if (is_in_str(to_find, tmp->str, len_str_to_find) == 0)
            return ((sub = ft_strdup(tmp->str)));
        tmp = tmp->next;
        size_list--;
    }
    return (NULL);
}


static void print_prompt_search(t_42sh *sh, int len_del, int choice, char *to_print_in, char *to_print_out)
{
    choice == 0 ? (len_del += 17) : (len_del += 25);
    to_print_out == NULL ? (len_del) : (len_del += ft_strlen(to_print_out));
    clean_line_lentoback(len_del);
    if (choice == 0)
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
        place_curs_ctrlr(sh, to_print_in, to_print_out, len_del);
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

void       ctrlr_read(t_42sh *sh, char *dup, char *arg, int i, int is_find)
{
    while (42)
    {
        if (!(arg = get_line_ctrlr(sh, arg, i)))
        {
            is_find == 0 \
            ? clean_line_lentoback(i + 25) : clean_line_lentoback(i + 17 + ft_strlen(dup));
            prompt(sh->env, sh);
            if (dup && sh->history_mark->error_code == 0)
            {
                get_new_line_ctrlr(sh, i, dup);    
                place_curs_ctrlr(sh, sh->history_mark->ctrlr_arg , dup, i);
                free(sh->history_mark->ctrlr_arg);
            }
            free(dup);
            return ;
        }
        if (dup)
            free(dup);
        if ((dup = search_history_ctrl_r(sh, arg, i)))
        {
            is_find = 1;
            print_prompt_search(sh, i ,0, arg, dup);
        }
        else
        {
            is_find = 0;
            print_prompt_search(sh, i , 1, arg, NULL);
        }
        i++;
       place_curs_ctrlr(sh, arg, dup, i);
    }
}

void       ctrlr_action(t_42sh *sh) //add nb_line 
{
    char    *arg;
    char    *dup;
    int     is_find;
    int     i;

    dup = NULL;
    is_find = 0;
    i = 0;
    arg = NULL;
    sh->history_mark->error_code = 0;
    sh->history_mark->ctrlr_arg = NULL;
    if (!(arg = (char*)malloc(sizeof(char) * 0)))
        return ;
    clean_line_lentoback(sh->prompt_len);
    print_prompt_search(sh, 0 ,0, NULL, NULL);
    sh->stdin->cursor_pos = 17;
    ctrlr_read(sh, dup, arg, i, is_find);
}