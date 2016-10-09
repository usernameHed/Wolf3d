/*
** main.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Fri Dec  5 17:23:50 2014 ugo belfiore
** Last update Sun Dec 21 08:01:15 2014 ugo belfiore
*/

#include "./include/my.h"
#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"

int		main()
{
  int		fd;
  t_file	f;
  int		rett;

  fd = open("./maps/map_rand.wolf", O_RDONLY);
  if (fd == -1)
    {
      my_printf("ERROR: can't open file\n");
      close(fd);
      return (0);
    }
  f.aleat = 1;
  rett = read(fd, f.buff, 40960);
  if (rett != 1830)
    {
      my_printf("don't touch map_rand.wolf file !\n");
      exit(0);
    }
  my_str_to_wordtab_fdf(&f);
  aff_win("SLENDER -       COLLECT EIGHT PAGES       - SLENDER", 900, 600, &f);
  close(fd);
  return (0);
}
