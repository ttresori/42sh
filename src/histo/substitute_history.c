/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:41:02 by ttresori          #+#    #+#             */
/*   Updated: 2019/01/10 20:31:25 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sh.h"

char	*substitute_history(t_42sh *sh)
{
	sh->to_replace = 0;
	if (sh->lexer->str[1] == '!')
		sh->to_replace = 1;
	if (sh->to_replace == 1)
	{
		sh->line_to_replace = ft_strdup(sh->history_mark->last->str);
	}	
	return (NULL);
}
