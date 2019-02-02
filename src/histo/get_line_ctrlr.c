#include "sh.h"

static  char   *get_char(char *arg, int pos, long buf)
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

char            *get_line_ctrlr(char *arg, int pos)
{
	long	buf;
	int		i;

	buf = 0;
    if ((i = read(0, &buf, 6)) > 0)
        return(get_char(arg, pos, buf));
    return (NULL);
}