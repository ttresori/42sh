#include "sh.h"

static  char   *check_exit(t_42sh *sh, char *arg, long buf)
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
        return (arg);
}

static  char   *del_one_c(t_42sh *sh, char *arg)
{
    char    *new;
    int     i;

    new = NULL;
    i = 0;
    if (!arg || sh->history_mark->pos_arg == 0)
    {
        if (arg)
            free(arg);
        return (NULL);
    }
    i = sh->history_mark->pos_arg - 1;
    if (i == -1)
    {
        ft_putchar('\n');
        if (!(new = (char*)malloc(sizeof(char) * 0)))
        {
         free(arg);
         return (NULL);
        }
    new[0] ='\0';
    free(arg);
    return (new);
    }
    if (!(new = (char*)malloc(sizeof(char) * i)))
    {
        free(arg);
        return (NULL);
    }
    while (i  < sh->history_mark->pos_arg)
    {
        new[i] = arg[i];
        i++;
    }
    free(arg);
    return (new);
}

static  char   *get_char(t_42sh *sh, char *arg, long buf)
{
        if (!(check_exit(sh, arg, buf)))
            return (NULL);
        if (buf == DEL)
        {
            if (sh->history_mark->pos_arg == 0)
            {
                sh->history_mark->is_find = 0;
                return (arg);
            }
            if (sh->history_mark->pos_arg == 1)
                sh->history_mark->pos_arg--;
            else
            {
           //arg = del_one_c(sh, arg);
                arg = ft_realloc(arg, sh->history_mark->pos_arg, sh->history_mark->pos_arg - 1);
                arg[sh->history_mark->pos_arg - 1] = '\0';
                sh->history_mark->pos_arg--;
                return (arg);
            }
        }
        if (sh->history_mark->pos_arg == 0)
        {
            arg = ft_realloc(arg, 0, 2);
            if (buf != DEL)
                arg[0] = buf;
            else
                arg[0] = '\0';
            arg[1] = '\0';
        }
        else
        {
            if (sh->history_mark->is_find  == 1)
            {
            arg = ft_realloc(arg, sh->history_mark->pos_arg + 1, sh->history_mark->pos_arg + 2);
            arg[sh->history_mark->pos_arg ] = buf;
            arg[sh->history_mark->pos_arg  + 1] = '\0';
            sh->history_mark->is_find = 0;
            }
        }
        sh->history_mark->error_code = 0;
        return (arg);
}

char            *get_line_ctrlr(t_42sh *sh, char *arg)
{
	long	buf;
	int		i;

	buf = 0;
    if ((i = read(0, &buf, 6)) > 0)
    {
        arg = get_char(sh, arg, buf);
        return(arg);
    }
    return (NULL);
}