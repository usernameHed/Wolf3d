/*
** my_change_hexa.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Sun Dec 14 20:26:57 2014 ugo belfiore
** Last update Sun Dec 21 17:34:42 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** fonction permettant de modifier la valeur d'un int contenant un hexa
** (de type 0x00000000).
**
** ici, on décrémente la valeur par le coeficient pour assombrir la couleur.
*/

int	my_putnbr_base_wolf(int cute, int coef)
{
  int	B;
  int	G;
  int	R;

  R = ((cute / 0x10000) >= 255) ? 255 : (cute / 0x10000);
  cute -= (R * 0x10000);
  R = ((R - coef) >= 0) ? (R - coef) : 0;
  G = ((cute / 0x100) >= 255) ? 255 : (cute / 0x100);
  cute -= (G * 0x100);
  G = ((G - coef) >= 0) ? (G - coef) : 0;
  B = (cute >= 255) ? 255 : cute;
  cute = 0;
  B = ((B - coef) >= 0) ? (B - coef) : 0;
  return ((B) + (G * 0x100) + (R * 0x10000));
}
