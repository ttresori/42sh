#include "tabulation.h"

int check_with_completion(t_42sh *sh, char *arg, struct dirent *ent)
{
	//if (arg[0] && ent->d_name[0])
		if (ft_strncmp(arg, ent->d_name, ft_strlen(arg)) == 0)
				return (1);
	return (2);
}

char		*detect_word_on_curs(t_42sh *sh)
{
	int	i2;
	int i;
	char *word;
	char *new_input;

	i2 = 0;
	i = sh->stdin->line_pos;
	new_input = NULL;
	if (sh->stdin->input[sh->stdin->line_pos] == '\0' && sh->stdin->input[sh->stdin->line_pos - 1] == ' ')
		{
			print_folder(sh, "./");
			ft_putchar_fd('\n', 0);
			clean_line_lentoback(sh->stdin->cursor_pos);
			prompt(sh->env, sh);
			ft_putstr_fd(sh->stdin->input, 0);
			return (NULL);
		}
	while (sh->stdin->input[i] != ' ')
		i--;
	//if (sh->stdin->input[i + 1] == '$') --> VARIABLE
	new_input = ft_strsub(sh->stdin->input, 0, i++);
	if (!(word = (char*)malloc(sizeof(char) * (sh->stdin->len_line - i))))
		return (NULL);
	while (sh->stdin->input[i] != ' ' && sh->stdin->input[i] != '\0')
		{
			word[i2] = sh->stdin->input[i];
			i2++;
			i++;
		}
	word[i2] = '\0';
	free(sh->stdin->input);
	sh->stdin->input = new_input;
	return (word);
}
