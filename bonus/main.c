/*
** main.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Fri Dec  5 17:23:50 2014 ugo belfiore
** Last update Sun Dec 21 17:51:10 2014 ugo belfiore
*/

#include "./include/my.h"
#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"

int		main(int ac, char **av)
{
  int		fd;
  t_file	f;
  int		rett;

  f.aleat = 0;
  ac = (ac == 2) ? ac : ac;
  fd = open(av[1], O_RDONLY);
  if (fd == -1)
    {
      fd = open("./maps/map_rand.wolf", O_RDONLY);
      if (fd == -1)
      	{
      	  my_printf("ERROR: can't open file\n");
      	  close(fd);
      	  return (0);
      	}
      f.aleat = 1;
    }
  rett = read(fd, f.buff, 40960);
  if (rett == 0 || rett > 40959)
    exit(0);
  my_str_to_wordtab_fdf(&f);
  aff_win("WOLF -   WHERE AM I - I'M FU**ING HERE !! -   WOLF", 900, 600, &f);
  close(fd);
  return (0);
}
