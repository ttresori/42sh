	#include "tabulation.h"

int check_with_completion(t_42sh *sh, char *arg, struct dirent *ent)
{
		if (ft_strncmp(arg, ent->d_name, ft_strlen(arg)) == 0)
				return (1);
	return (2);
}

int	search_env(char **env, int size, char *element)
{
	int pos;

	pos = 0;
	while (pos < size)
	{
		if (ft_strncmp(element, env[pos], ft_strlen(element)) == 0)
			return (pos);
		pos++;
	}
	return (-1);
}

int			size_env(char **env)
{
	int size;

	size = 0;
	while (env[size++]);
	return (size);
}

int			check_if_var_tab(t_42sh *sh, char *word)
{
	char **var_to_find;
	char *tmp;
	char **tmp2;
	int	nb_elem;

	var_to_find = ft_strsplitset(word, "$");
	nb_elem = 0;
	//if (var_to_find[1] == '\0')
		//print all var
	if ((nb_elem = search_env(sh->copy_env, size_env(sh->copy_env), var_to_find[0])) != -1)
		{
			tmp = ft_strjoin(sh->stdin->input, " ");
			free(sh->stdin->input);
			tmp2 = ft_strsplitset(sh->copy_env[nb_elem], "=");
			sh->stdin->input = ft_strjoin(tmp, tmp2[1]);
			free(tmp2);
			free(tmp);
			return (1);
		}
	return (1);
}

char		*detect_word_on_curs(t_42sh *sh)
{
	int	i2;
	int i;
	bool is_var;
	char *word;
	char *new_input;

	i2 = 0;
	i = sh->stdin->line_pos;
	new_input = NULL;
	is_var = 0;
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
	{
		if (is_var == false && sh->stdin->input[i] == '$')
			is_var = true;
		i--;
	}
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
	if (is_var == true)
	{
			check_if_var_tab(sh, word);
			return (NULL);
	}
	return (word);
}
