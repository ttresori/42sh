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

void	show_suggest(t_42sh *sh)
{
	char	**line;
	char	*tmp;
	char	*tmp2;
	char	*save_input;
	int		i;
	size_t		save_len_input;

	i = 0;
	save_len_input = sh->stdin->len_line;
	save_input = ft_strdup(sh->stdin->input);
	if (sh->stdin->len_line == 0)
	{
		print_folder(sh, "./");
		ft_putchar_fd('\n', 0);
		clean_line_lentoback(sh->stdin->cursor_pos);
		prompt(sh->env, sh);
		ft_putstr_fd(sh->stdin->input, 0);
		free(save_input);
		return ;
	}
	line = ft_strsplitset(sh->stdin->input, " \t\n");
	if (!(tmp = detect_word_on_curs(sh)))
	{
		if (line)
			ft_free_split(line);
		clean_line_lentoback(sh->stdin->cursor_pos);
		prompt(sh->env, sh);
		ft_putstr_fd(sh->stdin->input, 0);
		sh->stdin->len_line = ft_strlen(sh->stdin->input);
		sh->stdin->line_pos = sh->stdin->len_line;
		free(save_input);
		return ;
	}
	if (line)
	{
		if (show_name(sh, tmp, "./") == 2)
			{
				free(sh->stdin->input);
				sh->stdin->input = ft_strdup(save_input);
				ft_putchar_fd('\n', 0);
				free(tmp);
				clean_line_lentoback(sh->stdin->cursor_pos);
				prompt(sh->env, sh);
				ft_putstr_fd(sh->stdin->input, 0);
				free(save_input);
				return ;
			}
		ft_free_split(line);
	}
	if (save_len_input == ft_strlen(sh->stdin->input))
		{
			free(sh->stdin->input);
			sh->stdin->input = ft_strdup(save_input);
			ft_putchar_fd('\n', 0);
			free(tmp);
			clean_line_lentoback(sh->stdin->cursor_pos);
			prompt(sh->env, sh);
			ft_putstr_fd(sh->stdin->input, 0);
			free(save_input);
			return ;
		}
	free(tmp);
	//ft_putchar_fd('\n', 0);
	clean_print(sh);
	sh->stdin->len_line = ft_strlen(sh->stdin->input);
	sh->stdin->line_pos = sh->stdin->len_line;
	move_to_end(sh);
	free(save_input);
}
