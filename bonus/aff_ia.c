/*
** aff_ia.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Fri Dec 12 17:55:27 2014 ugo belfiore
** Last update Sun Dec 21 05:05:42 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** boucle principale du slenderman.
** le joueur laisse des bloc de type "11" derrière lui.
** à partir d'un certain nombre de mouvement, l'IA pop à la position
** initiale du joueur. A partir de la, un random va chercher les direction
** O/E/S/N pour suivre les bloc "11", une fois que L'IA passe sur ces bloc,
** elle change la position précédente de l'IA en "1" -> un couloir normale.
**
** Lorsque l'IA est bloqué (s'il n'y a pas de "11" dans les directions O/E/S/N
** un algo va parsé chaque case autour de l'IA à +1 case, puis +2 case,
** jusqu'a +n case (le dépacemetn de map est geré !) jusqu'a ce que cet algo
** trouve un "11" ou "2" le plus proche ! ("2" étant la position du joueur).
** une fois trouvé, l'IA pop sur cette case, et l'algo random reprend.
**
** si l'ia arrive sur le joueur (ou si le joueur arrive sur l'IA)
** c'est perdu !
*/

void	slender(t_data *d)
{
  srandom(time(NULL) * getpid());
  d->ia.hunt = 0;
  d->ia.start = 0;
  while (d->ia.hunt == 0)
    {
      d->ia.i = random() % 4;
      d->ia.blocked = 0;
      slender_rand_x(d);
      slender_rand_y(d);
      slender_blocked(d);
      d->ia.start++;
    }
  if (d->ia.hunt == 2)
    slender_hunt(d);
  aff_win_wolf(d, 0);
  mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
  if (d->p.out2 != 0)
    mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm2, 400, 35);
  if (d->ia.stop == 0)
    mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm3, 0, 369);
}

/*
** mouvement de l'IA en O/E.
*/

void	slender_rand_x(t_data *d)
{
  if (d->ia.i == O &&
      my_getnbr(d->tab[d->ia.popX + (d->ia.popY * d->x_file) - 0]) == 50 &&
      my_getnbr(d->tab[d->ia.popX + (d->ia.popY * d->x_file) - 1]) == 11)
    {
      d->tab[d->ia.popX + (d->ia.popY * d->x_file) - 0] = "1";
      d->tab[d->ia.popX + (d->ia.popY * d->x_file) - 1] = "50";
      d->ia.popX--;
      d->ia.blocked = 1;
    }
  if (d->ia.i == E &&
      my_getnbr(d->tab[d->ia.popX + (d->ia.popY * d->x_file) + 0]) == 50 &&
      my_getnbr(d->tab[d->ia.popX + (d->ia.popY * d->x_file) + 1]) == 11)
    {
      d->tab[d->ia.popX + (d->ia.popY * d->x_file) + 0] = "1";
      d->tab[d->ia.popX + (d->ia.popY * d->x_file) + 1] = "50";
      d->ia.popX++;
      d->ia.blocked = 1;
    }
}

/*
** mouvement de l'IA en N/S.
*/

void	slender_rand_y(t_data *d)
{
  if (d->ia.i == N &&
      my_getnbr(d->tab[d->ia.popX + ((d->ia.popY - 0) * d->x_file)]) == 50 &&
      my_getnbr(d->tab[d->ia.popX + ((d->ia.popY - 1) * d->x_file)]) == 11)
    {
      d->tab[d->ia.popX + ((d->ia.popY - 0) * d->x_file)] = "1";
      d->tab[d->ia.popX + ((d->ia.popY - 1) * d->x_file)] = "50";
      d->ia.popY--;
      d->ia.blocked = 1;
    }
  if (d->ia.i == S &&
      my_getnbr(d->tab[d->ia.popX + ((d->ia.popY + 0) * d->x_file)]) == 50 &&
      my_getnbr(d->tab[d->ia.popX + ((d->ia.popY + 1) * d->x_file)]) == 11)
    {
      d->tab[d->ia.popX + ((d->ia.popY + 0) * d->x_file)] = "1";
      d->tab[d->ia.popX + ((d->ia.popY + 1) * d->x_file)] = "50";
      d->ia.popY++;
      d->ia.blocked = 1;
    }
}

/*
** fonction qui test le random dans les différente direction possible
**	de l'ia.
** si blocked == 0, il n'est pas passé dans le premier random i = 0,E,N,S.
**	testons les 3 autres directions pour voir s'il peut passer.
**	 si il peut vraiment pas passer, il va chercher le carré gris
**	 le plus proche, et il va se tp. (hunt = 2);
** si blocked == 1, il est passé, on réinitialise save et on quitte la boucle.
**	(hunt = 1);
*/

void		slender_blocked(t_data *d)
{
  static int	save2[4] = {0, 0, 0, 0};
  int		res;

  if (d->ia.start == 0)
    save2[0] = save2[1] = save2[2] = save2[3] = 0;
  if (d->ia.blocked == 0)
    {
      save2[0] = (d->ia.i == 0) ? 1 : save2[0];
      save2[1] = (d->ia.i == 1) ? 1 : save2[1];
      save2[2] = (d->ia.i == 2) ? 1 : save2[2];
      save2[3] = (d->ia.i == 3) ? 1 : save2[3];
      res = d->ia.i;
      while (d->ia.i == res)
	d->ia.i = random() % 4;
      if (save2[0] == 1 && save2[1] == 1 && save2[2] == 1 && save2[3] == 1)
	{
	  d->ia.hunt = 2;
	  save2[0] = save2[1] = save2[2] = save2[3] = 0;
	}
    }
  else
    {
      save2[0] = save2[1] = save2[2] = save2[3] = 0;
      d->ia.hunt = 1;
    }
}
