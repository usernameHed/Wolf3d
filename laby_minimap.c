/*
** laby_minimap.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Sun Nov 30 20:48:37 2014 ugo belfiore
** Last update Sun Dec 21 17:29:30 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** boucle principal de création de la minimap.
** (est calculé par rapport à la taille de fenêtre).
*/

void		aff_win_minimap(t_data *d)
{
  t_minimap	m;

  m.i = 0;
  m.j = 0;
  m.pos = 0;
  m.xi = d->x_max / 5;
  laby_pos(d, &m);
  laby_i_j(d, &m);
  while (m.j < m.ymax)
    {
      while (m.i < m.xmax)
        {
          m.getpos = my_getnbr(d->tab[m.pos]);
          aff_win_minimap2(d, &m);
          m.i++;
          m.pos++;
        }
      if (m.xmax == 11)
	m.pos += d->x_file - m.xmax;
      m.i = 0;
      m.j++;
    }
}

/*
** change la couleur suivant le caractère actuelle du tableau.
** affiche la map en grand ou en petit sur le joueur suivant
** la valeur de Mod. (le bonus violet permet d'afficher la map en grand).
*/

void	aff_win_minimap2(t_data *d, t_minimap *m)
{
  if (m->getpos == 0)
    d->colo = 0xFFFFFF;
  else if (m->getpos == 1 || m->getpos == 11)
    d->colo = 0x000000;
  else if (m->getpos == 50)
    d->colo = 0x0033FF;
  else if (m->getpos == 2)
    {
      d->colo = 0xFF0000;
      d->p.pos = m->pos;
    }
  else if (m->getpos == 9)
    d->colo = 0x00FF00;
  else if (m->getpos == 8)
    d->colo = 0x33FF00;
  else if (m->getpos == 7)
    d->colo = 0xFF00FF;
  if (d->mod < 100)
    laby_scroll_all(d, m);
  else
    laby_scroll_min(d, m);
}

/*
** vérifie si on entre dans un bonus.
** bonus 7 (vert): ajoute 1 à la variable bonus.
** bonus 8 (violet): set mod à 0 (affiche la map en grand et non
**	en petit sur le joueur pour un temps limité).
*/

void	aff_win_minimove(t_data *d, int cc, int bb)
{
  d->mod = (my_getnbr(d->tab[cc + d->x_file * bb]) == 7) ? 0 : d->mod;
  if (my_getnbr(d->tab[cc + d->x_file * bb]) == 8)
    {
      d->p.b++;
      d->ia.wait -= 600000;
      d->ia.wait = (d->ia.wait < 100000) ? 100000 : d->ia.wait;
    }
  if (d->p.b >= 8)
    {
      d->ia.stop = 1;
      aff_win_win(d);
    }
}
