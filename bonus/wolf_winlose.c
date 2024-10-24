/*
** wolf_winlose.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Sat Dec 13 18:48:27 2014 ugo belfiore
** Last update Sun Dec 21 18:30:14 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** fonction de victoire.
** joue de son et affiche une image (stop tout jusqu'a l'appuis de F2).
*/

void	aff_win_win(t_data *d)
{
  d->ia.xpm = mlx_xpm_file_to_image(d->mlx_ptr,"./texture/win.xpm",
                                    &d->ia.save1, &d->ia.save2);
  if (!d->ia.xpm)
    exit(0);
  FMOD_System_PlaySound(d->sd.system, FMOD_CHANNEL_FREE,
			d->sd.win, 0, NULL);
  mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm, 0, 0);
}

/*
** fonction de défaite.
** joue de son et affiche une image (stop tout jusqu'a l'appuis de F2).
*/

void	aff_win_lose(t_data *d)
{
  d->ia.xpm = mlx_xpm_file_to_image(d->mlx_ptr,"./texture/lose.xpm",
				    &d->ia.save1, &d->ia.save2);
  if (!d->ia.xpm)
    exit(0);
  FMOD_System_PlaySound(d->sd.system, FMOD_CHANNEL_FREE,
			d->sd.die, 0, NULL);
  mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm, 0, 0);
}

/*
** petite fonction de str_to_wordtab modifié, je savais pas ou la mettre...
*/

void	cute_check_2(t_file *f, int i)
{
  i -= (f->x_file * 2);
  while (f->buff[i])
    {
      if (f->buff[i] != '0' && f->buff[i] != ' ' && f->buff[i] != '\n' &&
          f->buff[i] != '\0')
        f->buff[i] = '0';
      i++;
    }
}
