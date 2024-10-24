/*
** my_str_to_wordtab.c for  in /home/belfio_u/rendu/Piscine_C_J08/ex_04
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Fri Oct 24 19:29:19 2014 ugo belfiore
** Last update Sun Dec 21 18:27:02 2014 ugo belfiore
*/

#include <stdlib.h>
#include "./include/my.h"
#include "./include/mini.h"

int	cute_word(char *av)
{
  int	i;
  int	cpt;

  i = 0;
  cpt = 0;
  while (av[i])
    {
      if ((av[i] >= '0' && av[i] <= '9'))
        {
          cpt++;
          while (av[i] && ((av[i] >= '0' && av[i] <= '9')))
            i++;
        }
      i++;
    }
  return (cpt);
}

void	cute_check(t_file *f)
{
  int	i;
  int	testx;
  int	testy;

  i = -1;
  testx = 0;
  testy = 0;
  while (f->buff[++i])
    {
      if ((f->buff[i] >= '0' && f->buff[i] <= '9'))
        {
	  (f->buff[i] != '0' && testx == 0) ? exit(0) : 1;
          testx += (testy == 0) ? 0 : 1;
	  (f->buff[i] != '0' && testy == 0) ? exit(0) : 1;
          while (f->buff[i] && ((f->buff[i] >= '0' && f->buff[i] <= '9')))
            i++;
        }
      if (f->buff[i] == '\n')
        {
          testy++;
          testx = 0;
        }
    }
  cute_check_2(f, i);
}

void	cute_file(t_file *f)
{
  int	i;
  int	testx;

  i = -1;
  testx = 0;
  f->x_file = 0;
  f->y_file = 0;
  while (f->buff[++i])
    {
      if ((f->buff[i] != ' ' && f->buff[i] != '\n' &&
	   (f->buff[i] < '0' || f->buff[i] > '9')))
	exit(0);
      if ((f->buff[i] >= '0' && f->buff[i] <= '9'))
        {
	  (f->y_file == 0) ? f->x_file++ : testx++;
          while (f->buff[i] && ((f->buff[i] >= '0' && f->buff[i] <= '9')))
	    i++;
        }
      if (f->buff[i] == '\n')
	{
	  (f->y_file != 0 && testx != f->x_file) ? exit(0) : 1;
	  f->y_file++;
	  testx = 0;
	}
    }
}

int	cute_char(char *av, int *i)
{
  int	cpt;

  cpt = 0;
  while (av[*i] && ((av[*i] >= '0' && av[*i] <= '9')))
    {
      cpt++;
      *i = *i + 1;
    }
  return (cpt);
}

void	my_str_to_wordtab_fdf(t_file *f)
{
  int	i;
  int	a;

  i = 0;
  a = 0;
  cute_file(f);
  cute_check(f);
  f->word = cute_word(f->buff);
  f->tab = (char **)malloc(sizeof(char *) * f->word);
  while (f->buff[i] && f->word > 0)
    {
      if ((f->buff[i] >= '0' && f->buff[i] <= '9'))
        {
          f->tab[a] = my_strdup(f->buff + i);
          f->tab[a][cute_char(f->buff, &i)] = '\0';
          a++;
          f->word--;
        }
      i++;
    }
  f->tab[cute_word(my_strdup(f->buff))] = NULL;
}
