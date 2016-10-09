/*
** aff_ia_hunt.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Sat Dec 13 17:28:00 2014 ugo belfiore
** Last update Thu Dec 18 01:19:36 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** algo qui recherche la traçante du joueur "11", ou le joueur "2"
** le plus proche et recherchant autour de l'IA.
*/

void		slender_hunt(t_data *d)
{
  t_shunt	h;

  h.coef = 1;
  while (h.coef)
    {
      slender_hunt_ini(&h, d);
      while (h.i <= h.k)
	{
	  while (h.j <= h.l)
	    {
	      if (my_getnbr(d->tab[h.i + (h.j * d->x_file)]) == 11 ||
		  my_getnbr(d->tab[h.i + (h.j * d->x_file)]) == 2)
		{
		  slender_hunt_check(&h, d);
		  return;
		}
	      h.j++;
	    }
	  h.j = d->ia.popY - h.coef;
	  h.j = (h.j < 1) ? 1 : h.j;
	  h.i++;
	}
      h.coef++;
    }
}

/*
** initialise toute les variables permettant le parsing
** avec gestions de dépacement de map.
*/

void	slender_hunt_ini(t_shunt *h, t_data *d)
{
  h->i = d->ia.popX - h->coef;
  h->j = d->ia.popY - h->coef;
  h->k = d->ia.popX + h->coef;
  h->l = d->ia.popY + h->coef;
  h->i = (h->i < 1) ? 1 : h->i;
  h->j = (h->j < 1) ? 1 : h->j;
  h->k = (h->k > d->x_file - 2) ? d->x_file - 2 : h->k;
  h->l = (h->l > d->y_file - 2) ? d->y_file - 2 : h->l;
}

/*
** test si le bloc est un 11 ou un 2, si oui, pop l'IA !
** (si c'est un 11, fin de l'algo, si c'est un 2, perdu !
*/

void	slender_hunt_check(t_shunt *h, t_data *d)
{
  d->tab[d->ia.popX + (d->ia.popY * d->x_file)] = "1";
  if (my_getnbr(d->tab[h->i + (h->j * d->x_file)]) != 2)
    d->tab[h->i + (h->j * d->x_file)] = "50";
  else
    {
      d->ia.stop = 2;
      aff_win_lose(d);
    }
  d->ia.popX = h->i;
  d->ia.popY = h->j;
}
