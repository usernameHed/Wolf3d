/*
** evenement_norme.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Tue Dec 16 15:31:22 2014 ugo belfiore
** Last update Sun Dec 21 18:17:11 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** initialise variable PLAYER
*/

void	wolf_init(t_data *d, t_file *f)
{
  int	i;

  i = -1;
  d->p.posX = 0;
  d->p.posY = 0;
  d->p.aleat = f->aleat;
  d->p.dirX = -1;
  d->p.dirY = 0;
  d->p.planX = 0;
  d->p.planY = 0.62;
  d->mod = 0;
  d->tab = f->tab;
  d->x_file = f->x_file;
  d->y_file = f->y_file;
  d->p.b = 0;
  d->ia.pop = 0;
  d->ia.stop = 10;
  d->ia.once = 0;
  d->ia.wait = 4000000;
  d->p.out = 0;
  d->p.out2 = 0;
  d->p.ppp = 0;
  while (i++ < 5)
    d->p.faster[i] = 0;
  d->tab = (f->aleat == 1) ? laby_generate(d) : d->tab;
}

/*
** sert à initialiser la position initiale du joueur en trouvant
**      dans la map ou se trouve le caractère "2", qui sert ici de
**      position initial dans le labyrinthe.
**
** si il ne trouve pas de "2", la map est invalide et le programme se ferme.
*/

void	wolf_pos(t_data *d)
{
  int	i;
  int	j;
  int	pos;
  int	getpos;

  i = 0;
  j = 0;
  pos = 0;
  while (j < d->y_file)
    {
      while (i < d->x_file)
        {
          getpos = my_getnbr(d->tab[pos]);
          if (getpos == 2)
            {
              d->p.posX = i + 1;
              d->p.posY = (j + 1) - 0.45;
            }
          i++;
          pos++;
        }
      i = 0;
      j++;
    }
  (d->p.posX == 0) ? exit(0) : 1;
}

/*
** evenement qui s'active à chaque frame, utilse pour le déplacement de
** l'IA, le test de victoire et de défaite et le menu !
**
** le petit usleep pour ralentir le CPU !
*/

int		manage_frame(void *param)
{
  t_data	*d;

  d = (t_data *)param;
  usleep(400);
  manage_frame_test_key(d);
  if (d->ia.stop > 0 || d->ia.pop < 30)
    return (0);
  d->p.out += 7000;
  if (d->p.out > d->ia.wait)
    {
      slender(d);
      d->p.out = 0;
      d->p.ppp++;
      if (d->p.ppp >= 10)
	{
	  d->p.out2 = 0;
	  d->p.ppp = 0;
	}
    }
  return (0);
}

/*
** check si le tableau de touche directionnelle est remplie et si oui,
** active la fonction manage_key.
*/

void	manage_frame_test_key(t_data *d)
{
  if (d->ia.stop == 10)
    {
      d->ia.xpm = mlx_xpm_file_to_image(d->mlx_ptr,"./texture/slender.xpm",
					&d->ia.save1, &d->ia.save2);
      FMOD_Sound_SetLoopCount(d->sd.intro, -1);
      FMOD_System_PlaySound(d->sd.system, FMOD_CHANNEL_FREE,
                            d->sd.intro, 0, NULL);
      if (!d->ia.xpm)
	exit(0);
      d->ia.stop = 11;
      mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm, 0, 0);
    }
  if ((d->ia.stop == 2 || d->ia.stop == 1) && d->ia.once == 0)
    {
      mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm, 0, 0);
      d->ia.once++;
    }
  (d->p.faster[0] == 1) ? manage_key(KEY_UP, (void *)(d)) : 1;
  (d->p.faster[1] == 1) ? manage_key(KEY_DOWN, (void *)(d)) : 1;
  (d->p.faster[2] == 1) ? manage_key(KEY_TURNL, (void *)(d)) : 1;
  (d->p.faster[3] == 1) ? manage_key(KEY_TURNR, (void *)(d)) : 1;
  (d->p.faster[4] == 1) ? manage_key(KEY_LEFT, (void *)(d)) : 1;
  (d->p.faster[5] == 1) ? manage_key(KEY_RIGHT, (void *)(d)) : 1;
}

/*
** réinitialise toutes les variables du wolf lors de l'appui sur
**	la touche REFRESH (F2).
*/

void	manage_key_refresh(t_data *d)
{
  int	i;

  i = -1;
  d->mod = 0;
  d->ia.stop = 10;
  d->ia.pop = 0;
  d->tab = laby_generate(d);
  d->p.dirX = -1;
  d->p.dirY = 0;
  d->p.planX = 0;
  d->p.planY = 0.62;
  wolf_pos(d);
  d->p.posX += d->p.dirX * 0.3;
  d->p.posY += d->p.dirY * 0.3;
  d->ia.popX = d->p.posX;
  d->ia.popY = d->p.posY;
  d->ia.once = 0;
  d->p.out = 0;
  d->p.out2 = 0;
  d->p.ppp = 0;
  while (i++ < 5)
    d->p.faster[i] = 0;
  d->p.b = 0;
  d->sd.poney = -1;
  d->ia.wait = 4000000;
}
