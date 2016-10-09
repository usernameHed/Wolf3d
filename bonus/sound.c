/*
** sound.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d/bonus
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Sat Dec 20 16:54:25 2014 ugo belfiore
** Last update Sun Dec 21 18:28:30 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** focntion qui initialise les sons du wolf.
*/

void	sound(t_data *d)
{
  FMOD_System_Create(&d->sd.system);
  FMOD_System_Init(d->sd.system, 1, FMOD_INIT_NORMAL, NULL);
  FMOD_System_CreateSound(d->sd.system, "./texture/bonus1.wav",
  				 FMOD_CREATESAMPLE, 0, &d->sd.bonus1);
  FMOD_System_CreateSound(d->sd.system, "./texture/MEC003.wav",
  				 FMOD_CREATESAMPLE, 0, &d->sd.win);
  FMOD_System_CreateSound(d->sd.system, "./texture/die.wav",
  				 FMOD_CREATESAMPLE, 0, &d->sd.die);
  FMOD_System_CreateSound(d->sd.system, "./texture/intro_island.wav",
  				 FMOD_CREATESAMPLE, 0, &d->sd.intro);
}

/*
** fonction echap, qui echap le plus cleanement possible le programme.
*/

void	quitt(t_data *d)
{
  FMOD_Sound_Release(d->sd.bonus1);
  FMOD_System_Close(d->sd.system);
  FMOD_System_Release(d->sd.system);
  mlx_destroy_window(d->mlx_ptr, d->win_ptr);
  if (d->p.aleat == 1)
    free(d->tab);
  exit(1);
}
