/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:21:10 by ttresori          #+#    #+#             */
/*   Updated: 2019/01/25 02:58:32 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "dirent.h"

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

static int check_with_completion(t_42sh *sh, char *arg, struct dirent *ent)
{
	//if (arg[0] && ent->d_name[0])
		if (ft_strncmp(arg, ent->d_name, ft_strlen(arg)) == 0)
				return (1);
	return (0);
}

static void print_folder_with_compl(t_42sh *sh, char *word, char *path)
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
			tputs(tgoto(tgetstr("SR", NULL), 1, 0), 1, putchar_custom);
			tputs(tgoto(tgetstr("down", NULL), 1, 0), 1, putchar_custom);
			//clean_print(sh);
			move_to_end(sh);
			return ;
		}
	//tputs(tgoto(tgetstr("down", NULL), 1, 0), 1, putchar_custom);
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
	return_check = 1;
	while ((ent = readdir(directory)) != NULL)
	{
		if ((return_check = check_with_completion(sh, str_to_find, ent)) == 1)
		{
			if (!(tmp = ft_strjoin(sh->stdin->input, " ")))
				return (-1);
			if (sh->stdin->input)
				free(sh->stdin->input);
			if (!(sh->stdin->input = ft_strjoin(tmp, ent->d_name)))
				return (-1);
			return (1);
		}
		if (return_check == 2)
		{
			return (2);
		}
	}
	return (0);
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

void	show_suggest(t_42sh *sh)
{
	char	**line;
	char	*tmp;
	int		i;
	size_t		save_len_input;

	i = 0;
	save_len_input = sh->stdin->len_line;
	if (sh->stdin->len_line == 0)
	{
		print_folder(sh, "./");
		ft_putchar_fd('\n', 0);
		clean_line_lentoback(sh->stdin->cursor_pos);
		prompt(sh->env, sh);
		ft_putstr_fd(sh->stdin->input, 0);
		return ;
	}
	line = ft_strsplitset(sh->stdin->input, " \t\n");
	if (!(tmp = detect_word_on_curs(sh)))
		return ;
	if (line)
			show_name(sh, tmp, "./");
	ft_free_split(line);
	if (save_len_input == ft_strlen(sh->stdin->input))
		{
			print_folder_with_compl(sh, tmp, "./");
			ft_putchar_fd('\n', 0);
			free(tmp);
			clean_line_lentoback(sh->stdin->cursor_pos);
			prompt(sh->env, sh);
			ft_putstr_fd(sh->stdin->input, 0);
			return ;
		}
	free(tmp);
	//ft_putchar_fd('\n', 0);
	clean_print(sh);
	sh->stdin->len_line = ft_strlen(sh->stdin->input);
	sh->stdin->line_pos = sh->stdin->len_line;
	move_to_end(sh);
}
