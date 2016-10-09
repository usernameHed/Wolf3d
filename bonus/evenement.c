/*
** evenement.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Thu Dec  4 10:10:43 2014 ugo belfiore
** Last update Sun Dec 21 20:42:16 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** evenememnt clavier
** (gère l'exit, le déplacement dans le labyrinthe 3D & dans la minimap
**	ainsi le F2 (pour recommencer))
*/

int		manage_key(int keycode, void *param)
{
  t_data	*d;

  d = (t_data *)param;
  if (d->ia.stop == 11 && keycode != KEY_ENTER)
    {
      d->ia.stop = 0;
      aff_win_wolf(d, KEY_UP);
      aff_win_wolf(d, KEY_RIGHT);
    }
  d->mod = (d->mod < 100 && keycode == KEY_UP) ? d->mod + 1 : d->mod;
  if (keycode == KEY_KILL || keycode == KEY_ESC)
    exit(0);
  (keycode == KEY_REFRESH && d->p.aleat == 1) ? manage_key_refresh(d) : 1;
  if (d->ia.stop == 0)
    {
      d->p.out += (keycode == KEY_UP || keycode == KEY_DOWN) ? 80000 : 0;
      (d->p.out > d->ia.wait) ? slender(d) : 1;
      d->p.out = (d->p.out > d->ia.wait) ? 0 : d->p.out;
      aff_win_wolf(d, keycode);
      mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
      if (d->p.out2 != 0)
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm2, 400, 35);
      mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm3, 0, 369);
    }
  return (0);
}

/*
** evenement de répétition de touche de clavier
** sert à éfectuer l'action dès la saisi des touches du clavier,
**      et pas seulement après la saisi.
*/

int		manage_keyPres(int keycode, void *param)
{
  t_data	*d;

  d = (t_data *)param;
  if (keycode == KEY_KILL || keycode == KEY_ESC)
    quitt(d);
  if (keycode == KEY_PONEY)
    d->sd.poney *= -1;
  d->p.faster[0] = (keycode == KEY_UP && d->p.faster[1] == 0) ?
    1 : d->p.faster[0];
  d->p.faster[1] = (keycode == KEY_DOWN && d->p.faster[0] == 0) ?
    1 : d->p.faster[1];
  d->p.faster[2] = (keycode == KEY_TURNL && d->p.faster[3] == 0) ?
    1 : d->p.faster[2];
  d->p.faster[3] = (keycode == KEY_TURNR && d->p.faster[2] == 0) ?
    1 : d->p.faster[3];
  d->p.faster[4] = (keycode == KEY_LEFT && d->p.faster[5] == 0) ?
    1 : d->p.faster[4];
  d->p.faster[5] = (keycode == KEY_RIGHT && d->p.faster[4] == 0) ?
    1 : d->p.faster[5];
  d->mod = (d->mod == 1) ? d->mod : d->mod;
  if (d->ia.stop == 0)
    mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm3, 0, 369);
  return (0);
}

/*
** lorsque qu'une touche est laché, vérifie si cette touche fait partie
** des touche directionnelle, si oui, vider le tableau.
**
** ensuite appeler simplement la fonction manage_key une fois.
*/

int		manage_keyRelease(int keycode, void *param)
{
  t_data	*d;

  d = (t_data *)param;
  d->p.faster[0] = (keycode == KEY_UP) ? 0 : d->p.faster[0];
  d->p.faster[1] = (keycode == KEY_DOWN) ? 0 : d->p.faster[1];
  d->p.faster[2] = (keycode == KEY_TURNL) ? 0 : d->p.faster[2];
  d->p.faster[3] = (keycode == KEY_TURNR) ? 0 : d->p.faster[3];
  d->p.faster[4] = (keycode == KEY_LEFT) ? 0 : d->p.faster[4];
  d->p.faster[5] = (keycode == KEY_RIGHT) ? 0 : d->p.faster[5];
  manage_key(keycode, (void *)(d));
  return (0);
}

/*
** evenement expose
** est appelé dès que la fenêtre à besoin d'être recalculé
** réaffiche le ciel/sol, puis le wolf3D, puis la minimap
*/

int		manage_expose(void *param)
{
  t_data	*d;

  d = (t_data *)param;
  if (d->ia.stop == 0)
    aff_win_wolf(d, 0);
  if (d->ia.stop == 2 || d->ia.stop == 1)
    mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm, 0, 0);
  else
    mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
  d->ia.xpm3 = mlx_xpm_file_to_image(d->mlx_ptr,"./texture/torche.xpm",
				     &d->ia.save3, &d->ia.save4);
  if (!d->ia.xpm3)
    exit(0);
  if (d->ia.stop == 0)
    mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm3, 0, 369);
  return (0);
}

/*
** c'est ici que s'opère toute les opérations de la fenêtre du wolf
** la boucle loop se répète et appelera tout les évenement nécessaire.
*/

void		aff_win(char *name, int x_max, int y_max, t_file *f)
{
  t_data	d;

  d.x_max = x_max;
  d.y_max = y_max;
  sound(&d);
  wolf_init(&d, f);
  d.sd.poney = -1;
  wolf_pos(&d);
  d.p.posX += d.p.dirX * 0.3;
  d.p.posY += d.p.dirY * 0.3;
  d.ia.popX = d.p.posX;
  d.ia.popY = d.p.posY;
  d.mlx_ptr = mlx_init();
  if (d.mlx_ptr == NULL)
    exit(0);
  d.win_ptr = mlx_new_window(d.mlx_ptr, x_max, y_max, name);
  d.img_ptr = mlx_new_image(d.mlx_ptr, x_max, y_max);
  d.bigData = mlx_get_data_addr(d.img_ptr, &d.bpp, &d.sizeline, &d.endian);
  mlx_put_image_to_window(d.mlx_ptr, d.win_ptr, d.img_ptr, 0, 0);
  mlx_expose_hook(d.win_ptr, &manage_expose, (void *)(&d));
  mlx_hook(d.win_ptr, 2, 2, &manage_keyPres, (void *)(&d));
  mlx_hook(d.win_ptr, 3, 3, &manage_keyRelease, (void *)(&d));
  mlx_loop_hook(d.mlx_ptr, &manage_frame, (void *)(&d));
  mlx_loop(d.mlx_ptr);
}
