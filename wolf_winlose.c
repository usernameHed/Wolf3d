/*
** wolf_winlose.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Sat Dec 13 18:48:27 2014 ugo belfiore
** Last update Sun Dec 21 09:03:12 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

void	aff_win_win(t_data *d)
{
  my_printf("%d",d->ia.stop);
  d->ia.xpm = mlx_xpm_file_to_image(d->mlx_ptr,"./texture/win.xpm",
                                    &d->ia.save1, &d->ia.save2);
  if (!d->ia.xpm)
    exit(0);
  mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm, 0, 0);
}

void	aff_win_lose(t_data *d)
{
  d->ia.xpm = mlx_xpm_file_to_image(d->mlx_ptr,"./texture/lose.xpm",
				    &d->ia.save1, &d->ia.save2);
  if (!d->ia.xpm)
    exit(0);
  mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->ia.xpm, 0, 0);
}

void    cute_check_2(t_file *f, int i)
{
  i -= 59;
  while (f->buff[i])
    {
      if (f->buff[i] != '0' && f->buff[i] != ' ' && f->buff[i] != '\n' &&
	  f->buff[i] != '\0')
	f->buff[i] = '0';
      i++;
    }
}
