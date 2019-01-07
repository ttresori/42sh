/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 22:52:07 by ttresori          #+#    #+#             */
/*   Updated: 2019/01/07 23:40:56 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*substitute_history(t_42sh *sh)
{
	int replaced;

	replaced = 0;
	if (sh->lexer->str[1] == '!')
		replaced = 1;
	if (replaced == 1)
	{
		ft_putstr(sh->history_mark->last->str);
	}
	
	return (NULL);
}
