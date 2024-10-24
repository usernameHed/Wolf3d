/*
** aff_wolf_img_strafe.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Tue Dec 16 18:29:08 2014 ugo belfiore
** Last update Sun Dec 21 18:36:03 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** parmet le déplacement latérale
*/

/*
** a droite
*/

void    aff_wolf_strafe_right(t_data *d, int keycode, t_moo *m)
{
  if (keycode == KEY_RIGHT)
    {
      m->tmpDirX = d->p.dirX;
      d->p.dirX = d->p.dirX * cos(-m->t) - d->p.dirY * sin(-m->t);
      d->p.dirY = m->tmpDirX * sin(-m->t) + d->p.dirY * cos(-m->t);
      m->tmpPlanX = d->p.planX;
      d->p.planX = d->p.planX * cos(-m->t) - d->p.planY * sin(-m->t);
      d->p.planY = m->tmpPlanX * sin(-m->t) + d->p.planY * cos(-m->t);
      m->bb = d->p.posY;
      m->cc = d->p.posX;
      m->aa = d->p.posX + d->p.dirX * m->moveDir;
      m->dd = d->p.posY + d->p.dirY * m->moveDir;
      d->tab[m->cc + d->x_file * m->bb] = "11";
      aff_wolf_strafe_right_bis(d, m);
    }
}

void	aff_wolf_strafe_right_bis(t_data *d, t_moo *m)
{
  if (my_getnbr(d->tab[m->aa + d->x_file * m->bb]) != 0)
    d->p.posX += d->p.dirX * m->moveCheck;
  if (my_getnbr(d->tab[m->cc + d->x_file * m->dd]) != 0)
    d->p.posY += d->p.dirY * m->moveCheck;
  m->bb = d->p.posY;
  m->cc = d->p.posX;
  aff_win_minimove(d, m->cc, m->bb);
  if (my_getnbr(d->tab[m->cc + d->x_file * m->bb]) == 50)
    {
      d->tab[m->cc + d->x_file * m->bb] = "2";
      d->ia.stop = 2;
      aff_win_lose(d);
    }
  d->tab[m->cc + d->x_file * m->bb] = "2";
  m->tmpDirX = d->p.dirX;
  d->p.dirX = d->p.dirX * cos(m->t) - d->p.dirY * sin(m->t);
  d->p.dirY = m->tmpDirX * sin(m->t) + d->p.dirY * cos(m->t);
  m->tmpPlanX = d->p.planX;
  d->p.planX = d->p.planX * cos(m->t) - d->p.planY * sin(m->t);
  d->p.planY = m->tmpPlanX * sin(m->t) + d->p.planY * cos(m->t);
}

/*
** a gauche
*/

void    aff_wolf_strafe_left(t_data *d, int keycode, t_moo *m)
{
  if (keycode == KEY_LEFT)
    {
      m->tmpDirX = d->p.dirX;
      d->p.dirX = d->p.dirX * cos(m->t) - d->p.dirY * sin(m->t);
      d->p.dirY = m->tmpDirX * sin(m->t) + d->p.dirY * cos(m->t);
      m->tmpPlanX = d->p.planX;
      d->p.planX = d->p.planX * cos(m->t) - d->p.planY * sin(m->t);
      d->p.planY = m->tmpPlanX * sin(m->t) + d->p.planY * cos(m->t);
      m->bb = d->p.posY;
      m->cc = d->p.posX;
      m->aa = d->p.posX + d->p.dirX * m->moveDir;
      m->dd = d->p.posY + d->p.dirY * m->moveDir;
      d->tab[m->cc + d->x_file * m->bb] = "11";
      aff_wolf_strafe_left_bis(d, m);
    }
}

void	aff_wolf_strafe_left_bis(t_data *d, t_moo *m)
{
  if (my_getnbr(d->tab[m->aa + d->x_file * m->bb]) != 0)
    d->p.posX += d->p.dirX * m->moveCheck;
  if (my_getnbr(d->tab[m->cc + d->x_file * m->dd]) != 0)
    d->p.posY += d->p.dirY * m->moveCheck;
  m->bb = d->p.posY;
  m->cc = d->p.posX;
  aff_win_minimove(d, m->cc, m->bb);
  if (my_getnbr(d->tab[m->cc + d->x_file * m->bb]) == 50)
    {
      d->tab[m->cc + d->x_file * m->bb] = "2";
      d->ia.stop = 2;
      aff_win_lose(d);
    }
  d->tab[m->cc + d->x_file * m->bb] = "2";
  m->tmpDirX = d->p.dirX;
  d->p.dirX = d->p.dirX * cos(-m->t) - d->p.dirY * sin(-m->t);
  d->p.dirY = m->tmpDirX * sin(-m->t) + d->p.dirY * cos(-m->t);
  m->tmpPlanX = d->p.planX;
  d->p.planX = d->p.planX * cos(-m->t) - d->p.planY * sin(-m->t);
  d->p.planY = m->tmpPlanX * sin(-m->t) + d->p.planY * cos(-m->t);
}
