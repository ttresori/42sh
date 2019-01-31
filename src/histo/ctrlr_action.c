#include "sh.h"

static char			*get_line_ctrlr(char **arg, int pos)
{
	long	buf;
	int		i;
    char    *new;

	buf = 0;
    new = NULL;
	if ((i = read(0, &buf, 6)) > 0)
	{
        if (buf == '\n')
            return (NULL);
        if (pos == 0)
        {
            if (!(new = (char*)malloc(sizeof(char) * 2)))
                return (*arg);
            new[2] = '\0';
        }
        else
        {
            if (!(new = (char*)malloc(sizeof(char) * (pos + 1))))
                return (*arg);
            new = ft_strncpy(*arg, new, pos);
        }
        new[pos] = buf;
        new[pos + 1] = '\0';
		return (new);
	}
    return (NULL);
}

void    ctrlr_action(t_42sh *sh)
{
    char    *arg;
    int     i;

    arg = NULL;
    i = 0;
  /*  if (!(arg = (char*)malloc(sizeof(char) * 2)))
        return ;
    arg[0] = '\0';*/
    ft_putchar('\n');
    ft_putstr("Search :");
    while (42)
    {
        if (!(arg = get_line_ctrlr(&arg, i)))
        {
           // ft_puts_blue(arg);
            return ;
        }
        ft_putchar(arg[i]);
        i++;
    }
}