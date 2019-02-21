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

static void check_with_completion(t_42sh *sh, char *arg, struct dirent *ent)
{
	if (ft_strncmp(arg, ent->d_name, ft_strlen(arg)) == 0)
	{
			free(sh->stdin->input);
			sh->stdin->input = ft_strdup(ent->d_name);
	}
}

int		show_name(t_42sh *sh, char *str_to_find, char *path)
{
	DIR	*directory;
	struct dirent *ent;
	int i;

	i = 0;
	directory = opendir(path);
	while ((ent = readdir(directory)) != NULL)
	{
		check_with_completion(sh, str_to_find, ent);
		i++;
	}
	return (0);
}

void	show_suggest(t_42sh *sh)
{
	char	**line;
	int		save_pos;
	int		i;

	i = 0;
	line = ft_strsplitset(sh->stdin->input, " \t\n");
	//ft_putchar('\n');
	if (line)
	{
		if (line[0] == NULL)
			line[0] = ft_strdup(sh->stdin->input);
		while (line[i])
		{
			show_name(sh, line[i], "./");
			i++;
		}
	}
	ft_free_split(line);
	clean_print(sh);
	sh->stdin->len_line = ft_strlen(sh->stdin->input);
	sh->stdin->line_pos = sh->stdin->len_line;
	move_to_end(sh);
	//tputs(tgoto(tgetstr("up", NULL), 1, 0), 1, putchar_custom);
	//move_to_end(sh);
	//clean_line_lentoback(sh->stdin->cursor_pos);
	//sh->prompt_len = 0;
	//prompt(sh->env, sh);
	//ft_putstr(sh->stdin->input);
	//sh->stdin->line_pos = ft_strlen(sh->stdin->input);
	//sh->stdin->len_line = sh->stdin->line_pos;
	//sh->stdin->cursor_pos += sh->stdin->len_line;
//	directory = NULL;
}
