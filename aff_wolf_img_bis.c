/*
** aff_wolf_img_bis.c for  in /home/belfio_u/rendu/MUL_2014_wolf3d
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Thu Nov 27 12:34:07 2014 ugo belfiore
** Last update Sun Dec 21 17:41:36 2014 ugo belfiore
*/

#include "./lib/minilibx/mlx.h"
#include "./include/mini.h"
#include "./include/my.h"

/*
** tant qu'on touche as un mur (hit = 0) on saute les carré X, Y.
** si après le calcule, on se trouve dans un carré ou il y a un mur/bonus:
**      hit = 0 et on sort de la boucle
**
** PS: s'il n'y a pas de mur, il y a boucle infini ! il est donc
** important dans le fichier map de bien fermer la map avec des mur
** pour éviter tout problème
*/

void	aff_wolf_hit(t_rayc *r, t_data *d)
{
  while (r->hit == 0)
    {
      if (r->sideDistX < r->sideDistY)
        {
          r->sideDistX += r->deltaDistX;
          r->mapX += r->stepX;
          r->side = 0;
        }
      else
        {
          r->sideDistY += r->deltaDistY;
          r->mapY += r->stepY;
          r->side = 1;
        }
      if (my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) == 0 ||
          my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) == 8 ||
          my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) == 7 ||
          my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) == 50)
        r->hit = 1;
    }
}

/*
** calcule la hauteur vertical du mur à afficher
**	par rapport à la fenêtre et la distance joueur/mur
**
** ligne vertical en X (valeur courante de la boucle) =
**	de y1 = drawStart à y2 = drawEnd
*/

void	aff_wolf_distray(t_rayc *r)
{
  r->wallDist = (r->side == 0) ?
    fabs((r->mapX - r->rayPosX + (1 - r->stepX) / 2) / r->rayDirX)
  : fabs((r->mapY - r->rayPosY + (1 - r->stepY) / 2) / r->rayDirY);
  r->lineHeight = abs(r->tmp_ymax / r->wallDist);
  r->drawStart = (r->lineHeight * -1) / 2 + r->tmp_ymax / 2;
  r->drawStart = (r->drawStart < 0) ? 0 : r->drawStart;
  r->drawEnd = r->lineHeight / 2 + r->tmp_ymax / 2;
  r->drawEnd = (r->drawEnd >= r->tmp_ymax) ? r->tmp_ymax - 1 : r->drawEnd;
}

/*
** choisi la couleur (en hexa) suivant le numéro dans le fichier map
** (0 = mur rouge, 8 = bonus vert, 7 = bonus violet)
** diviser la couleur par 3 si side = 1 pour différencier le flanc doit/gauche
**
** enfin, affiche la ligne verticale X, y1, y2 !
*/

void	aff_wolf_color(t_rayc *r, t_data *d)
{
  int	i;
  int	add;

  i = -1;
  d->colo = COLOR_SKY;
  while (i++ < r->drawStart)
    {
      aff_pix_img(d, r->x, i);
      d->colo = my_putnbr_base_wolf(d->colo, 1);
    }
  aff_wolf_color_mirror(r, d);
  d->colo = (r->side == 1) ? d->colo - (d->colo / 3) : d->colo;
  add = (r->tmp_ymax < 300) ? 300 : 0;
  d->colo = (my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) != 50) ?
    dark_pixel(d, ((r->tmp_ymax + add) / 2) - r->lineHeight) :
    dark_pixel(d, ((r->tmp_ymax + add) / 2) - r->lineHeight - 150);
  while (r->drawStart++ < r->drawEnd)
    aff_pix_img(d, r->x, r->drawStart);
  aff_wolf_color_mirror(r, d);
  d->colo = dark_pixel(d, ((r->tmp_ymax + add) / 2) - r->lineHeight - 50);
  while (r->drawEnd++ < r->tmp_ymax)
    {
      aff_pix_img(d, r->x, r->drawEnd);
      d->colo = my_putnbr_base_wolf(d->colo, 2);
    }
}

/*
** affiche le dégradé vers le bas (l'effet mirroir).
*/

void	aff_wolf_color_mirror(t_rayc *r, t_data *d)
{
  if (my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) == 0)
    d->colo = COLOR_BLOCK;
  if (my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) == 8)
    d->colo = COLOR_BONUS;
  if (my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) == 7)
    d->colo = COLOR_BONUS_MAP;
  if (my_getnbr(d->tab[r->mapX + d->x_file * r->mapY]) == 50)
    d->colo = COLOR_IA;
}

/*
** gere les fleches pour aller avant/arrière
** (besoin de changer PosX et PosY de notre player dans d.p)
*/

void	aff_wolf_key_move(t_data *d, int keycode)
{
  t_moo	m;

  m.moveDir = 0.3;
  m.moveCheck = 0.1;
  m.bb = d->p.posY;
  m.cc = d->p.posX;
  aff_wolf_move_up(d, keycode, &m);
  aff_wolf_move_down(d, keycode, &m);
  m.t = 1.5708;
  aff_wolf_turn(d, keycode, &m);
  aff_wolf_strafe_right(d, keycode, &m);
  aff_wolf_strafe_left(d, keycode, &m);
}
