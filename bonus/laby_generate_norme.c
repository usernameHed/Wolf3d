/*
** laby_generate_norme.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Sun Nov 30 22:38:30 2014 ugo belfiore
** Last update Thu Dec 18 01:22:24 2014 ugo belfiore
*/

#include "./include/my.h"
#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"

/*
** ces fonctions servent uniquement à mettre à la norme la fonction
** labyhunt !
*/

void	laby_hunt_bis(t_laby *y)
{
  y->xx = 0;
  y->yy = 1;
  y->tab[(y->xPos) + (y->yPos * y->xlen) - 1] = "9";
}

void	laby_hunt_tris(t_laby *y, int i)
{
  if (my_getnbr(y->tab[i]) != y->xlen)
    y->xx++;
  if (y->xx == y->xlen)
    {
      y->xx = 0;
      y->yy++;
    }
}

void	laby_hunt_quad(t_laby *y, int i)
{
  y->tab[i] = "2";
  y->xPos = y->xx;
  y->yPos = y->yy - 1;
  y->clean = 1;
  y->hunt = 0;
}
