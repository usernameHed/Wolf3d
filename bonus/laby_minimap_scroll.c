/*
** laby_minimap_scroll.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Mon Dec  1 10:19:42 2014 ugo belfiore
** Last update Thu Dec 18 01:22:48 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** affiche le rectangle à la bonne position.
** (pour la map en grand).
*/

void	laby_scroll_all(t_data *d, t_minimap *m)
{
  aff_rec(d, (m->xi * 4) + (m->sx * m->i),
          (m->yi * 2) + (m->sy * m->j),
          ((m->xi * 4) + (m->sx * m->i)) + m->sx,
          ((m->yi * 2) + (m->sy * m->j)) + m->sy);
}

/*
** affiche le rectangle à la bonne position.
** (pour la map en petit sur le joueur).
*/

void	laby_scroll_min(t_data *d, t_minimap *m)
{
  m->sx = m->xi / 11;
  m->sy = m->yi / 11;
  aff_rec(d, (m->xi * 4) + (m->sx * m->i),
          (m->yi * 2) + (m->sy * m->j),
          ((m->xi * 4) + (m->sx * m->i)) + m->sx,
          ((m->yi * 2) + (m->sy * m->j)) + m->sy);
}

/*
** fonction qui enregistre la position du joueur dans posX & posY.
*/

void	laby_pos(t_data *d, t_minimap *m)
{
  m->yi = d->y_max / 3;
  m->sx = m->xi / d->x_file;
  m->sy = m->yi / d->y_file;
  m->posX = 0;
  m->posY = 0;
  while (m->j < d->y_file)
    {
      while (m->i < d->x_file)
        {
          m->getpos = my_getnbr(d->tab[m->pos]);
          if (m->getpos == 2)
	    {
	      m->posX = m->i + 1;
	      m->posY = m->j + 1;
	    }
          m->i++;
          m->pos++;
        }
      m->i = 0;
      m->j++;
    }
  m->i = 0;
  m->j = 0;
  m->pos = 0;
}

/*
** fonction qui, suivant la valeur de mod, initialise les variables
** de création de la minimap de façon à afficher la minimap:
**	- soit dans sa totalité.
**	- soit seulement en 11 * 11 suivant la position du joueur.
**	  suivant la position du joueur, la caméra fait en sorte
**	  de toujours être au centre du joueur, sauf lorsqu'il est au
**	  au bord de la map.
*/

void	laby_i_j(t_data *d, t_minimap *m)
{
  int	value1;
  int	value2;

  if (d->mod == 100)
    {
      value1 = m->posX;
      value2 = m->posY;
      if (m->posX < 6)
	value1 = 6;
      if (m->posX > d->x_file - 5)
	value1 = d->x_file - 5;
      if (m->posY < 6)
	value2 = 6;
      if (m->posY > d->y_file - 5)
	value2 = d->y_file - 5;
      m->pos = (value1 + ((value2 - 1) * d->x_file)) - 6 - (5 * d->x_file);
      m->xmax = 11;
      m->ymax = 11;
    }
  else
    {
      m->xmax = d->x_file;
      m->ymax = d->y_file;
    }
}
