#include "tabulation.h"

void	print_folder(t_42sh *sh, char *path)
{
	DIR	*directory;
	struct dirent *ent;

	directory = opendir(path);
	ft_putchar('\n');
	while ((ent = readdir(directory)) != NULL)
	{
		ft_putstr(ent->d_name);
		ft_putchar('\t');
	}
	//tputs(tgoto(tgetstr("up", NULL), 1, 0), 1, putchar_custom);
	move_to_end(sh);
}

void print_folder_with_compl(t_42sh *sh, char *word, char *path)
{
	DIR *dir;
	struct dirent *ent;
	int len_word;
	int i;

	dir = opendir(path);
	len_word = ft_strlen(word);
	i = 0;
	ft_putchar('\n');
	while ((ent = readdir(dir)) != NULL)
	{
		if (ft_strncmp(word, ent->d_name, len_word) == 0)
		{
			ft_putstr_fd(ent->d_name, 0);
			ft_putchar('\t');
			i++;
		}
	}
	if (i == 1)
		{
			tputs(tgoto(tgetstr("down", NULL), 1, 0), 1, putchar_custom);
			move_to_end(sh);
			return ;
		}
	move_to_end(sh);
}

int		show_name(t_42sh *sh, char *str_to_find, char *path)
{
	DIR	*directory;
	struct dirent *ent;
	int i;
	int return_check;
	char *tmp;

	i = 0;
	directory = opendir(path);
	return_check = 0;
	while ((ent = readdir(directory)) != NULL)
	{
		if ((return_check = check_with_completion(sh, str_to_find, ent)) == 1)
		{
            if (i > 0)
            {
                print_folder_with_compl(sh, str_to_find, path);
                return (2);
            }
			if (!(tmp = ft_strjoin(sh->stdin->input, " ")))
				return (-1);
			if (sh->stdin->input)
				free(sh->stdin->input);
			if (!(sh->stdin->input = ft_strjoin(tmp, ent->d_name)))
				return (-1);
			free(tmp);
            i++;
		}
	}
	return (0);
}