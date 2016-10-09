/*
** aff_wolf_img_key.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Tue Dec 16 17:10:42 2014 ugo belfiore
** Last update Sun Dec 21 18:34:56 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** permet de bouger dans le wolf.
**
** - précalcule l'avancement,
** - laisse à l'emplacement actuelle un couloir,
** - si l'avancement calculé ne se trouve aps dans un mur, augmente la position
**      (grace aux vecteur).
** - réaffiche le player en remettant "2" dans le nouvelle emplacement.
*/

/*
** vers l'avant.
*/

void	aff_wolf_move_up(t_data *d, int keycode, t_moo *m)
{
  if (keycode == KEY_UP)
    {
      m->aa = d->p.posX + d->p.dirX * m->moveDir;
      m->dd = d->p.posY + d->p.dirY * m->moveDir;
      d->tab[m->cc + d->x_file * m->bb] = "11";
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
      d->ia.pop++;
    }
}

/*
** vers l'arrière.
*/

void	aff_wolf_move_down(t_data *d, int keycode, t_moo *m)
{
  if (keycode == KEY_DOWN)
    {
      m->aa = d->p.posX - d->p.dirX * m->moveDir;
      m->dd = d->p.posY - d->p.dirY * m->moveDir;
      d->tab[m->cc + d->x_file * m->bb] = "11";
      if (my_getnbr(d->tab[m->aa + d->x_file * m->bb]) != 0)
        d->p.posX -= d->p.dirX * m->moveCheck;
      if (my_getnbr(d->tab[m->cc + d->x_file * m->dd]) != 0)
        d->p.posY -= d->p.dirY * m->moveCheck;
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
      d->ia.pop++;
    }
}

/*
** permet de tourner dans le wolf.
** - change le vecteur direction,
** - change les vecteurs caméra.
*/

void	aff_wolf_turn(t_data *d, int keycode, t_moo *m)
{
  if (keycode == KEY_TURNR)
    {
      m->tmpDirX = d->p.dirX;
      d->p.dirX = d->p.dirX * cos(-m->t / 40) - d->p.dirY * sin(-m->t / 40);
      d->p.dirY = m->tmpDirX * sin(-m->t / 40) + d->p.dirY * cos(-m->t / 40);

      m->tmpPlanX = d->p.planX;
      d->p.planX = d->p.planX * cos(-m->t / 40) - d->p.planY * sin(-m->t / 40);
      d->p.planY = m->tmpPlanX * sin(-m->t / 40) +
	d->p.planY * cos(-m->t / 40);
    }
  if (keycode == KEY_TURNL)
    {
      m->tmpDirX = d->p.dirX;
      d->p.dirX = d->p.dirX * cos(m->t / 40) - d->p.dirY * sin(m->t / 40);
      d->p.dirY = m->tmpDirX * sin(m->t / 40) + d->p.dirY * cos(m->t / 40);

      m->tmpPlanX = d->p.planX;
      d->p.planX = d->p.planX * cos(m->t / 40) - d->p.planY * sin(m->t / 40);
      d->p.planY = m->tmpPlanX * sin(m->t / 40) + d->p.planY * cos(m->t / 40);
    }
}
