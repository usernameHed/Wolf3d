/*
** aff_wolf_img.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Tue Nov 25 17:25:56 2014 ugo belfiore
** Last update Thu Dec 18 11:37:46 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** FU**ING RAYCASTING !
*/

/*
** set quelque veriable
** le raycasting va être exécuté deux fois (une fois pour le rétro !)
**	(en modifiant bien sur différente variable).
*/

void		aff_win_wolf(t_data *d, int keycode)
{
  t_rayc	r;
  t_retro	o;

  o.i = 0;
  r.x = -1;
  r.tmp_xmax = d->x_max;
  r.tmp_ymax = d->y_max;
  r.w = r.tmp_xmax;
  if (keycode != 0)
    aff_wolf_key_move(d, keycode);
  o.turn = -3.1416;
  while (o.i++ < 2)
    aff_win_wolf_ray(&r, d, &o);
  aff_win_minimap(d);
}

/*
** le raycasting normal s'éfectue une première fois avec les ancienne valeurs.
*/

void	aff_win_wolf_ray(t_rayc *r, t_data *d, t_retro *o)
{
  while (r->x++ < r->tmp_xmax)
    {
      aff_wolf_init(r, d);
      aff_wolf_step(r);
      aff_wolf_hit(r, d);
      aff_wolf_distray(r);
      aff_wolf_color(r, d);
    }
  aff_win_wolf_retro(r, d, o);
}

/*
** après le premier raycasting, change tout pour afficher le retro.
** (mais fait en sorte qu'après le rétro tout se remette correctement
**	pour la prochain raycasting normal !
*/

void	aff_win_wolf_retro(t_rayc *r, t_data *d, t_retro *o)
{
  o->turn *= -1;
  r->x = 20;
  r->tmp_xmax = (d->x_max / 5) + 20;
  r->tmp_ymax = d->y_max / 5;
  r->w = r->tmp_xmax;
  o->tmpDirX = d->p.dirX;
  d->p.dirX = d->p.dirX * cos(o->turn) - d->p.dirY * sin(o->turn);
  d->p.dirY = o->tmpDirX * sin(o->turn) + d->p.dirY * cos(o->turn);
  o->tmpPlanX = d->p.planX;
  d->p.planX = d->p.planX * cos(o->turn) - d->p.planY * sin(o->turn);
  d->p.planY = o->tmpPlanX * sin(o->turn) + d->p.planY * cos(o->turn);
}

/*
** initialise toute les variable du wolf
** cameraX = -1 pour la gauche de l'écran (2 * 0 / 10 - 1) = -1
**         = 0  pour le milieu de l'écran (2 * 5 / 10 - 1) = 0
**         = 1  pour la droite de l'écran (2 * 10 / 10 - 1) = 1
*/

void	aff_wolf_init(t_rayc *r, t_data *d)
{
  r->hit = 0;
  r->rayPosX = d->p.posX;
  r->rayPosY = d->p.posY;
  r->mapX = r->rayPosX;
  r->mapY = r->rayPosY;
  r->cameraX = 2 * r->x / r->w - 1;
  r->rayDirX = d->p.dirX + d->p.planX * r->cameraX;
  r->rayDirY = d->p.dirY + d->p.planY * r->cameraX;
  r->deltaDistX = sqrt(1 +(r->rayDirY * r->rayDirY) /
		       (r->rayDirX * r->rayDirX));
  r->deltaDistY = sqrt(1 + (r->rayDirX * r->rayDirX) /
		       (r->rayDirY * r->rayDirY));
}

/*
** calcule step et initialise sideDist
** step: à 1 ou -1 suivant si la direction est négative ou positive
**	(elle servira pour les calcules de traçages du mur)
**
** sideDistX: distance entre la case dans laquelle se trouve le player et
**	une autre case en X (même procédé pour Y).
*/

void	aff_wolf_step(t_rayc *r)
{
  r->stepX = (r->rayDirX < 0) ? -1 : 1;
  r->stepY = (r->rayDirY < 0) ? -1 : 1;
  r->sideDistX = (r->rayDirX < 0) ?
    (r->rayPosX - r->mapX) * r->deltaDistX
  : (r->mapX + 1.0 - r->rayPosX) * r->deltaDistX;
  r->sideDistY = (r->rayDirY < 0) ?
    (r->rayPosY - r->mapY) * r->deltaDistY
  : (r->mapY + 1.0 - r->rayPosY) * r->deltaDistY;
}
