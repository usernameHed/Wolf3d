/*
** my_change_hexa.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Sun Dec 14 20:26:57 2014 ugo belfiore
** Last update Sun Dec 21 18:25:49 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** change la valeur de cute.
** assombri cette valeur en hexa grace au coeficient.
*/

int	my_putnbr_base_wolf(int cute, int coef, int poney)
{
  int	B;
  int	G;
  int	R;

  if (poney == -1)
    R = ((cute / 0x10000) >= 255) ? 255 : (cute / 0x10000);
  else
    R = ((cute / 54000) >= 7) ? 255 : (cute / 54000);
  if (poney == -1)
    cute -= (R * 0x10000);
  else
    cute -= (R * 26);
  R = ((R - coef) >= 0) ? (R - coef) : 0;
  if (poney == -1)
    G = ((cute / 0x100) >= 255) ? 255 : (cute / 0x100);
  else
    G = ((cute / 0x1450001) >= 255) ? 255 : (cute / 134542);
  cute -= (G * 0x100);
  G = ((G - coef) >= 0) ? (G - coef) : 0;
  B = (cute >= 255) ? 255 : cute;
  cute = 0;
  B = ((B - coef) >= 0) ? (B - coef) : 0;
  return ((B) + (G * 0x100) + (R * 0x10000));
}
