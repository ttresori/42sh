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
	char	*save_input;
	char	*tmp;
	char	*tmp2;
	int		save_pos;
	int		i;

	i = 0;
	line = ft_strsplitset(sh->stdin->input, " \t\n");
	save_input = ft_strdup(line[0]);
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
	tmp2 = ft_strjoin(save_input, " ");
	tmp = ft_strjoin(tmp2, sh->stdin->input);
	free(sh->stdin->input);
	sh->stdin->input = ft_strdup(tmp);
	free(tmp);
	free(tmp2);
	clean_print(sh);
	sh->stdin->len_line = ft_strlen(sh->stdin->input);
	sh->stdin->line_pos = sh->stdin->len_line;
	move_to_end(sh);
}
