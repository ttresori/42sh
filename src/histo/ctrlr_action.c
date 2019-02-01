#include "sh.h"

static char			*get_line_ctrlr(char *arg, int pos)
{
	long	buf;
	int		i;

	buf = 0;
    if ((i = read(0, &buf, 6)) > 0)
	{
        if (buf == '\n' || buf == CTRL_C)
        {
            free(arg);
            return (NULL);
        }
        if (pos == 0)
        {
            arg = ft_realloc(arg, 0, 2);
            arg[pos] = buf;
            arg[1] = '\0';
        }
        else
        {
            arg = ft_realloc(arg, pos + 1, pos + 2);
            arg[pos] = buf;
            arg[pos + 1] = '\0';
        }
        return (arg);
	}
    return (NULL);
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

void    clean_line_lentoback(int len_to_left)
{

    while (len_to_left >= 0)
    {
        tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
        len_to_left--;
    }
    tputs(tgetstr("dl", NULL), 0, putchar_custom);
}

static void print_prompt_search(int len_del, int choice, char *to_print_in, char *to_print_out)
{
    choice == 0 ? (len_del += 16) : (len_del += 24);
    to_print_out == NULL ? (len_del) : (len_del += ft_strlen(to_print_out));
    clean_line_lentoback(len_del);
    if (choice == 0)
    {
        ft_puts_green("bck-i-search`");
        if (to_print_in)
            ft_puts_yellow(to_print_in);
        ft_puts_green("`: ");
        if (to_print_out)
            ft_putstr(to_print_out);
        return ;
    }
    ft_puts_green("failing bck-i-search`");
    if (to_print_in)
        ft_puts_cyan(to_print_in);
    ft_puts_green("`: ");
    if (to_print_out)
        ft_putstr(to_print_out);
}

void       double_free(char *s1, char *s2)
{
    if (s1)
        ft_strdel(&s1);
    if (s2)
        ft_strdel(&s2);
}

void       get_new_line_ctrlr(t_42sh *sh, int i, char *dup)
{
        get_substitute(sh, i, dup, 0);
        sh->stdin->len_line += ft_strlen(dup);
        sh->stdin->line_pos += ft_strlen(dup);
}

void       ctrlr_action(t_42sh *sh) //add nb_line 
{
    char    *arg;
    char    *dup;
    static int     is_find;
    int     i;

    dup = NULL;
    is_find = 0;
    i = 0;
    arg = NULL;
    if (!(arg = (char*)malloc(sizeof(char) * 0)))
        return ;
    clean_line_lentoback(sh->prompt_len);
    is_find == 0 \
    ? print_prompt_search(0 ,0, NULL, NULL): print_prompt_search(0, 1, NULL, NULL);
    while (42)
    {
        if (!(arg = get_line_ctrlr(arg, i)))
        {
            is_find == 1 \
            ? clean_line_lentoback(i + 24) : clean_line_lentoback(i + 16 + ft_strlen(dup));
            prompt(sh->env, sh);
            if (dup)
                get_new_line_ctrlr(sh, i, dup);
            double_free(arg, dup);
            return ;
        }
        if (dup)
            free(dup);
        if ((dup = search_history_ctrl_r(sh, arg, i)))
        {
            is_find = 1;
            print_prompt_search(i ,0, arg, dup);
        }
        else
            is_find == 0 \
            ? print_prompt_search(i ,0, arg, NULL): print_prompt_search(i, 1, arg, NULL);
        i++;
    }
}