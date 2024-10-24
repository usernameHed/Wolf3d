/*
** laby_generate_hunt.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Fri Nov 28 23:39:32 2014 ugo belfiore
** Last update Thu Dec 18 01:21:46 2014 ugo belfiore
*/

#include "./include/my.h"
#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"

/*
** après avoir été bloqué, laby_hunt va rechercher un autre endroit
** dans le labyrinthe où il y a un couloir pour reprendre le random
** dans les 4 direction.
** ce procédé est répété 30 fois, ensuite le labytinthe est fini.
*/

void		laby_hunt(t_laby *y)
{
  static int	i = 0;
  static int	j = 0;

  if (y->restart == 0)
    {
      i = 0;
      j = 0;
      y->restart++;
    }
  laby_hunt_bis(y);
  while (y->tab[i])
    {
      laby_hunt_tris(y, i);
      if (my_getnbr(y->tab[i]) == 1)
	{
	  if (j == 30 + random() % 10)
	    return;
	  laby_hunt_quad(y, i);
	  i = 1;
	  j++;
	  return;
	}
      i++;
    }
}

/*
** lors de la création du labytinthe, les mur au été set à 9 ou 2.
** (utiles pour la création du laby).
** lorsque le labyrinthe est fini, ces nombre doivent être remplacé par
**	1 ou 0 (pour donner des mur/couloir dans le laby).
*/

void	laby_clean(t_laby *y)
{
  int	res;

  y->ii = 0;
  y->xx = 0;
  y->yy = 1;
  laby_clean_bis(y);
  res = 0;
  while (res == 0)
    {
      y->xPos = 2 + random() % (y->xlen - 3);
      y->yPos = 2 + random() % (y->ylen - 3);
      res = 1;
      if (my_getnbr(y->tab[y->xPos + (y->yPos * y->xlen) - 1]) == 1)
	y->tab[y->xPos + (y->yPos * y->xlen) - 1] = "2";
      else
	res = 0;
    }
}

void	laby_clean_bis(t_laby *y)
{
  while (y->tab[y->ii])
    {
      if (my_getnbr(y->tab[y->ii]) != y->xlen)
        y->xx++;
      if (y->xx == y->xlen)
        {
          y->xx = 0;
          y->yy++;
        }
      if (my_getnbr(y->tab[y->ii]) == 9)
        y->tab[y->ii] = "1";
      if (my_getnbr(y->tab[y->ii]) == 2)
        y->tab[y->ii] = "0";
      if (my_getnbr(y->tab[y->ii]) == 1 && (y->xx < 2 || y->xx > y->xlen - 3))
        y->tab[y->ii] = "0";
      y->ii++;
    }
}

/*
** créé 10 bonus vert et 1 bonus violet dans tout le labyrinthe.
** en faisant attention de de rien mettre à la place d'un mur.
*/

void	laby_bonus(t_laby *y)
{
  int	res;
  int	xPos;
  int	yPos;

  res = 0;
  while (res <= 10)
    {
      xPos = 2 + random() % (y->xlen - 3);
      yPos = 2 + random() % (y->ylen - 3);
      res++;
      if (my_getnbr(y->tab[xPos + (yPos * y->xlen) - 1]) == 1 &&
	  my_getnbr(y->tab[xPos + (yPos * y->xlen) - 1]) != 2 &&
	  my_getnbr(y->tab[xPos + (yPos * y->xlen) - 1]) != 8 &&
	  my_getnbr(y->tab[xPos + (yPos * y->xlen) - 1]) != 7)
	{
	  if (res == 1)
	    y->tab[xPos + (yPos * y->xlen) - 1] = "7";
	  else
	    y->tab[xPos + (yPos * y->xlen) - 1] = "8";
	}
      else
        res--;
    }
}
