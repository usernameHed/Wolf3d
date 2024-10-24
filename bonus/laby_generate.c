/*
** laby_generate.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Thu Nov 27 19:54:56 2014 ugo belfiore
** Last update Thu Dec 18 01:21:32 2014 ugo belfiore
*/

#include "./include/my.h"
#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"

/*
** boucle principale de la création du labyrinthe aléatoire.
** (change les valeurs du tableau jusqu'a créé un labyrinthe complet).
**
** -créé un couloir de 2 vers la droite/gauche/haut/bas par rapport a '2'
** -si on est bloqué, parser le labytinthe pour trouver une autre issue.
*/

char		**laby_generate(t_data *d)
{
  t_laby	y;

  srandom(time(NULL) * getpid());
  laby_init(&y, d);
  while (y.hunt == 0)
    {
      y.i = random() % 4;
      y.blocked = 0;
      laby_rand_x(&y);
      laby_rand_y(&y);
      laby_blocked(&y);
      if (y.hunt == 1)
	laby_hunt(&y);
      y.start++;
    }
  laby_clean(&y);
  laby_bonus(&y);
  return (y.tab);
}

/*
** créé un couloir du coté OUEST/EST par raport au joueur.
*/

void	laby_rand_x(t_laby *y)
{
  if (y->i == O && y->xPos >= 6 &&
      my_getnbr(y->tab[(y->xPos) + (y->yPos * y->xlen) - 1]) == 2 &&
      my_getnbr(y->tab[(y->xPos) + (y->yPos * y->xlen) - 2]) == 0)
    {
      y->tab[(y->xPos) + (y->yPos * y->xlen) - 1] = "1";
      y->tab[(y->xPos) + (y->yPos * y->xlen) - 2] = "1";
      y->tab[(y->xPos) + (y->yPos * y->xlen) - 3] = "2";
      y->xPos -= 2;
      y->blocked = 1;
    }
  if (y->i == E && y->xPos < y->xlen - 4 &&
      my_getnbr(y->tab[(y->xPos) + (y->yPos * y->xlen) - 1]) == 2 &&
      my_getnbr(y->tab[(y->xPos) + (y->yPos * y->xlen) + 0]) == 0)
    {
      y->tab[(y->xPos) + (y->yPos * y->xlen) - 1] = "1";
      y->tab[(y->xPos) + (y->yPos * y->xlen) + 0] = "1";
      y->tab[(y->xPos) + (y->yPos * y->xlen) + 1] = "2";
      y->xPos += 2;
      y->blocked = 1;
    }
}

/*
** créé un couloir du coté NORD/SUD par raport au joueur.
*/

void	laby_rand_y(t_laby *y)
{
  if (y->i == N && y->yPos >= 5 &&
      my_getnbr(y->tab[(y->xPos) + ((y->yPos - 0) * y->xlen) - 1]) == 2 &&
      my_getnbr(y->tab[(y->xPos) + ((y->yPos - 1) * y->xlen) - 1]) == 0)
    {
      y->tab[(y->xPos) + ((y->yPos - 0) * y->xlen) - 1] = "1";
      y->tab[(y->xPos) + ((y->yPos - 1) * y->xlen) - 1] = "1";
      y->tab[(y->xPos) + ((y->yPos - 2) * y->xlen) - 1] = "2";
      y->yPos -= 2;
      y->blocked = 1;
    }
  if (y->i == S && y->yPos < y->ylen - 5 &&
      my_getnbr(y->tab[(y->xPos) + ((y->yPos + 0) * y->xlen) - 1]) == 2 &&
      my_getnbr(y->tab[(y->xPos) + ((y->yPos + 1) * y->xlen) - 1]) == 0)
    {
      y->tab[(y->xPos) + ((y->yPos + 0) * y->xlen) - 1] = "1";
      y->tab[(y->xPos) + ((y->yPos + 1) * y->xlen) - 1] = "1";
      y->tab[(y->xPos) + ((y->yPos + 2) * y->xlen) - 1] = "2";
      y->yPos += 2;
      y->blocked = 1;
    }
}

/*
** si on est bloqué dans les 4 angles possible:
** réinitialise blocked et recherche une autre issue à un autre endroit.
*/

void		laby_blocked(t_laby *y)
{
  static int	save[4] = {0, 0, 0, 0};
  int		res;

  if (y->start == 0 || y->clean == 1)
    {
      save[0] = save[1] = save[2] = save[3] = 0;
      y->clean = 0;
    }
  if (y->blocked == 0)
    {
      save[0] = (y->i == 0) ? 1 : save[0];
      save[1] = (y->i == 1) ? 1 : save[1];
      save[2] = (y->i == 2) ? 1 : save[2];
      save[3] = (y->i == 3) ? 1 : save[3];
      res = y->i;
      while (y->i == res)
        y->i = random() % 4;
      if (save[0] == 1 && save[1] == 1 && save[2] == 1 && save[3] == 1)
        y->hunt++;
    }
  else
    save[0] = save[1] = save[2] = save[3] = 0;
}

/*
** initialiste toute les variable du labytinthe ainsi que la position
** aléatoire du joueur dans la map.
*/

void	laby_init(t_laby *y, t_data *d)
{
  int	i;

  i = 0;
  y->tab = d->tab;
  y->start = 0;
  while (y->tab[i])
    {
      y->tab[i] = "0";
      i++;
    }
  y->xPos = 2 + random() % (d->x_file - 3);
  y->yPos = 2 + random() % (d->y_file - 3);
  y->xlen = d->x_file;
  y->ylen = d->y_file;
  y->tab[y->xPos + (y->yPos * y->xlen) - 1] = "2";
  y->hunt = 0;
  y->blocked = 0;
  y->restart = 0;
  y->clean = 0;
}
