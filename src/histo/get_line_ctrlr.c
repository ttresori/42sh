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

void            place_curs_ctrlr(t_42sh *sh, char *arg, char *dup, int len_arg)
{
    int i;
    int nb_to_move;

    i = 0;
    nb_to_move = 0;
    if (!arg || !dup)
            return ;
    if ((nb_to_move = get_first_c_of_occurence(arg, dup, len_arg)) > -1)
    {
        nb_to_move = ft_strlen(dup) - nb_to_move;
        sh->stdin->cursor_pos = (sh->stdin->cursor_pos - nb_to_move);
        sh->stdin->line_pos = sh->stdin->line_pos - nb_to_move;
        while(nb_to_move-- > 0)
            tputs(tgoto(tgetstr("le", NULL), 1, 0), 1, putchar_custom);
    }
}

static  char   *get_char(t_42sh *sh, char *arg, int pos, long buf)
{
        if (buf == '\n' || buf == CTRL_D)
        {
            sh->history_mark->error_code = 0;
            sh->history_mark->ctrlr_arg = ft_strdup(arg);
            free(arg);
            return (NULL);
        }
        if (buf == CTRL_C)
        {
            sh->history_mark->error_code = 1;
            sh->history_mark->ctrlr_arg = ft_strdup(arg);
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
        sh->history_mark->error_code = 0;
        return (arg);
}

char            *get_line_ctrlr(t_42sh *sh, char *arg, int pos)
{
	long	buf;
	int		i;

	buf = 0;
    if ((i = read(0, &buf, 6)) > 0)
        return(get_char(sh, arg, pos, buf));
    return (NULL);
}