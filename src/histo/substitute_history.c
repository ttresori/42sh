/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:41:02 by ttresori          #+#    #+#             */
/*   Updated: 2019/01/22 10:53:32 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "sh.h"

void	modify_last_history(t_42sh *sh)
{
  int i;
  int i2;
  int size;
  int fd;

  i = 0;
  i2 = 0;
  size = 0;
  fd = 0;
  fd = open(sh->path_history, O_RDWR);
  lseek(fd, sh->history_mark->size, SEEK_END);
  free(sh->history_mark->begin->next->next->str);
    while (sh->argv->argv[size] != NULL)
      size++;
  sh->history_mark->begin->next->next->str = (char*)malloc(sizeof(char) * size + 1);
    size = 0;
    while (sh->argv->argv[i] != NULL)
    {
      ft_putstr_fd(sh->argv->argv[i], fd);
      while (sh->argv->argv[i2] != '\0')
	{
	  sh->history_mark->begin->next->next->str[size] = sh->argv->argv[i][i2];
	  i2++;
	  size++;
	}
      i2 = 0;
      i++;
    }
    sh->history_mark->begin->next->next->str[size + 1] = '\0';
    ft_putstr(sh->history_mark->begin->next->next->str);
  ft_putstr_fd("\0", fd);
  close(fd);
}

/*void	check_substitute_histo(t_42sh *sh)
{
  int ask_substitute;

  ask_substitute = 0;
  sh->argv->cur_str = 0;
  while (sh->argv->argv[sh->argv->cur_str] != NULL)
    {
      sh->argv->pos_str = 0;
      while(sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str])
	{
	  if (sh->argv->argv[sh->argv->cur_str][sh->argv->pos_str] == '!')
	 {   
	   if (substitute_history(sh) == 0)
			return ;
	   else
	     ask_substitute = 1;
	 }
	  else
	    sh->argv->pos_str++;
	}
	sh->argv->cur_str++;
    }
  if (ask_substitute == 1)
    {
      modify_last_history(sh);
    }
}*/

void	get_substitute(t_42sh *sh, int nb_del, char *substitute)
{
  int i;
  char *tmp;
  char *tmp2;
  char *tmp3;

  i = 0;
  if (ft_strlen(sh->argv->argv[sh->argv->cur_str]) - nb_del == 0)
	{
		ft_strdel(&sh->argv->argv[sh->argv->cur_str]);
		sh->argv->argv[sh->argv->cur_str] = ft_strdup(substitute);
	}
  else
  {
  if (!(tmp = ft_strsub(sh->argv->argv[sh->argv->cur_str], 0, sh->argv->pos_str)))
    return ;
  tmp2 = ft_strsub(sh->argv->argv[sh->argv->cur_str], (sh->argv->pos_str + nb_del),
		   (ft_strlen(sh->argv->argv[sh->argv->cur_str]) - (ft_strlen(tmp) - nb_del)));
    tmp3 = ft_strjoin(tmp, substitute);
  ft_strdel(&sh->argv->argv[sh->argv->cur_str]);
  sh->argv->argv[sh->argv->cur_str] = ft_strjoin(tmp3, tmp2);
  free(tmp);
  free(tmp2);
  free(tmp3);
	}
}

int		substitute_history(t_42sh *sh)
{
  int pos_str;
  int nb_del;
  int replace_true;
  char *substitute;

  replace_true = 0;
  sh->to_replace = 0;
  sh->argv->pos_str = 0;
  pos_str = 0;  
  nb_del = 0;
  substitute = NULL;
  if ((sh->argv->argv[sh->argv->cur_str][pos_str] == '!')
      && (sh->argv->argv[sh->argv->cur_str][pos_str + 1] != '\0')
      && (sh->argv->argv[sh->argv->cur_str][pos_str + 1] == '!'))
  {
	  substitute = ft_strdup(sh->history_mark->begin->next->next->str);
	  ft_putendl(substitute);
	  get_substitute(sh, 2,substitute);
	  nb_del = 2;
	  sh->argv->pos_str = sh->argv->pos_str + nb_del + ft_strlen(substitute);
	  return (1);
	}
  ft_strdel(&substitute);
return (0);
}

/*
"! + numéro -> fin numéro"
"! + lettres -> espace ou! -> ! "
*/
