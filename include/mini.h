/*
** mini.h for  in /home/belfio_u/rendu/EXOTEST/FDF
** 
** Made by ugo belfiore
** Login   <belfio_u@epitech.net>
** 
** Started on  Tue Oct 28 09:26:37 2014 ugo belfiore
** Last update Sun Dec 21 17:55:12 2014 ugo belfiore
*/

#ifndef MINI_H_
#define MINI_H_

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>

/*
** define: couleur en hexadécimale.
*/

#define COLOR_YELLOW 0xFFFF00
#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLOCK 0xFF0000
#define COLOR_BONUS 0x33FF00
#define COLOR_BONUS_MAP 0xFF00FF
#define COLOR_IA 0x0033FF
#define COLOR_SKY 0x0000CC
#define COLOR_GROUND 0x330000

/*
** define: clavier.
*/

#define KEY_ENTER 65293
#define KEY_ESC 65307
#define KEY_REFRESH 65471
#define KEY_KILL 107
#define KEY_RIGHT 65363
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_TURNR 100
#define KEY_TURNL 113

/*
** define: orientation dans le labyrinthe aléatoire.
**	(OUEST, EST, NORD, SUD).
*/

#define O 0
#define E 2
#define N 1
#define S 3

/*
** rayc: toute les variable utiles du raytracing.
*/

typedef struct	s_rayc
{
  int		x;
  double	w;
  double	cameraX;
  double	rayPosX;
  double	rayPosY;
  double	rayDirX;
  double	rayDirY;
  int		mapX;
  int		mapY;
  double	sideDistX;
  double	sideDistY;
  double	deltaDistX;
  double	deltaDistY;
  double	wallDist;
  int		stepX;
  int		stepY;
  int		hit;
  int		side;
  int		lineHeight;
  int		drawStart;
  int		drawEnd;
  int		tmp_xmax;
  int		tmp_ymax;
}		t_rayc;

/*
** variable utile pour créé le rétro.
*/

typedef struct	s_retro
{
  int		i;
  double	tmpDirX;
  double	tmpPlanX;
  double	turn;
}		t_retro;

typedef struct	s_shunt
{
  int		coef;
  int		i;
  int		j;
  int		k;
  int		l;
}		t_shunt;

typedef struct	s_moo
{
  int		aa;
  int		bb;
  int		cc;
  int		dd;
  double	moveDir;
  double	moveCheck;
  double	tmpDirX;
  double	tmpPlanX;
  double	t;
}		t_moo;

/*
** player: contenue dans structure data, contient les variable
**	du joueur dans le labbyrinthe 3d.
*/

typedef struct  s_player
{
  int           pos;
  double	posX;
  double	posY;
  double	dirX;
  double	dirY;
  double	planX;
  double	planY;
  int		aleat;
  int		b;
  int		faster[6];
  int		out;
}               t_player;

/*
** variable ia:
** activation de l'ia ainsi que sa position.
*/

typedef struct	s_ia
{
  int		stop;
  int		start;
  void		*xpm;
  int		save1;
  int		save2;
  int		once;
  int		wait;
}		t_ia;

/*
** data: structure principale contenant les pointeurs
**	de fenêtreet d'image, contient le tableau **tab,
**	ainsi que les variable de t_player.
*/

typedef struct	s_data
{
  void		*mlx_ptr;
  void		*win_ptr;
  void		*img_ptr;
  char		*bigData;
  int		x_max;
  int		y_max;
  int		colo;
  int		bpp;
  int		sizeline;
  int		endian;
  char		**tab;
  int		x_file;
  int		y_file;
  int		mod;
  t_player	p;
  t_ia		ia;
}               t_data;

/*
** minimap: variable de la minimap
** (avec gestion du scrolling et de la taille variable
**	de la map dans le jeu).
*/

typedef struct	s_minimap
{
  int		xi;
  int		yi;
  int		sx;
  int		sy;
  int		pos;
  int		getpos;
  int		i;
  int		j;
  int		posX;
  int		posY;
  int		xmax;
  int		ymax;
}		t_minimap;

/*
** file: variable du parsing du fichier.
** enregistre le fichier dans **tab,
**	enregistre les dimensions du ficher dans x/y_file
*/

typedef struct	s_file
{
  char          buff[40960];
  int		word;
  char		**tab;
  int		x_file;
  int		y_file;
  int		aleat;
}		t_file;

/*
** fonction divers.
*/

void	aff_pix_img(t_data *d, int x, int y);
void	aff_rec(t_data *d, int x1, int y1, int x2, int y2);
int	cute_word(char *av);
int	cute_char(char *av, int *i);
void	cute_file(t_file *f);
void	cute_check_2(t_file *f, int i);
void	my_str_to_wordtab_fdf(t_file *f);
void	my_show_wordtab(char **tab);
void	wolf_init(t_data *d, t_file *f);
void	wolf_pos(t_data *d);
void	aff_win(char *name, int x_max, int y_max, t_file *f);
void	aff_win_win(t_data *d);
void	aff_win_lose(t_data *d);
int	dark_pixel(t_data *d, int coef);

/*
** fonction evenement minilibix
*/

void	manage_key_refresh(t_data *d);
int	manage_frame(void *param);
int	manage_key(int keycode, void *param);
void	manage_frame_test_key(t_data *d);

/*
** ombrage des murs
*/

int	my_putnbr_base_wolf(int nbr, int coef);

/*
** fonction de la minimap.
*/

void	aff_win_minimap(t_data *d);
void	aff_win_minimap2(t_data *d, t_minimap *m);
void	aff_win_minimove(t_data *d, int cc, int bb);
void	laby_pos(t_data *d, t_minimap *m);
void	laby_i_j(t_data *d, t_minimap *m);
void	laby_scroll_all(t_data *d, t_minimap *m);
void	laby_scroll_min(t_data *d, t_minimap *m);

/*
** fonction d'affichage du wolf en 3d.
*/

void	aff_win_wolf(t_data *d, int keycode);
void	aff_win_wolf_ray(t_rayc *r, t_data *d, t_retro *o);
void	aff_win_wolf_retro(t_rayc *r, t_data *d, t_retro *o);
void	aff_wolf_init(t_rayc *r, t_data *d);
void	aff_wolf_step(t_rayc *r);
void	aff_wolf_hit(t_rayc *r, t_data *d);
void	aff_wolf_distray(t_rayc *r);
void	aff_wolf_color(t_rayc *r, t_data *d);
void	aff_wolf_color_mirror(t_rayc *r, t_data *d);

/*
** fonction de déplacement du wolf
*/

void	aff_wolf_key_move(t_data *d, int keycode);
void	aff_wolf_move_up(t_data *d, int keycode, t_moo *m);
void	aff_wolf_move_down(t_data *d, int keycode, t_moo *m);
void	aff_wolf_turn(t_data *d, int keycode, t_moo *m);
void	aff_wolf_strafe_right(t_data *d, int keycode, t_moo *m);
void	aff_wolf_strafe_right_bis(t_data *d, t_moo *m);
void	aff_wolf_strafe_left(t_data *d, int keycode, t_moo *m);
void	aff_wolf_strafe_left_bis(t_data *d, t_moo *m);

/*
** fonction de l'IA.
*/

void	slender(t_data *d);
void	slender_rand_x(t_data *d);
void	slender_rand_y(t_data *d);
void	slender_blocked(t_data *d);
void	slender_hunt(t_data *d);
void	slender_hunt_ini(t_shunt *h, t_data *d);
void	slender_hunt_check(t_shunt *h, t_data *d);

#endif
