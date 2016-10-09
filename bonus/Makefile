##
## Makefile for  in /home/belfio_u/rendu/EXOTEST/FDF
## 
## Made by ugo belfiore
## Login   <belfio_u@epitech.net>
## 
## Started on  Mon Oct 27 15:13:44 2014 ugo belfiore
## Last update Sun Dec 21 21:51:17 2014 ugo belfiore
##

SRC     =       main.c			\
		evenement.c		\
		evenement_norme.c	\
		aff_pix_img.c		\
		my_str_to_wordtab_fdf.c	\
		aff_wolf_img.c		\
		aff_wolf_img_bis.c	\
		aff_wolf_img_key.c	\
		aff_wolf_img_strafe.c	\
		laby_generate.c		\
		laby_generate_hunt.c	\
		laby_generate_norme.c	\
		laby_minimap.c		\
		laby_minimap_scroll.c	\
		aff_ia.c		\
		aff_ia_hunt.c		\
		wolf_winlose.c		\
		my_change_hexa.c	\
		sound.c

OBJ     =       $(SRC:.c=.o)

NAME    =       wolf3d

LIB     =       lib/my/libmy.a

LIBMINI =	lib/minilibx/libmlx.a

CC      =       gcc

CFLAGS  +=      -W -Wall -Wextra

#LDFLAGS	=	-L/usr/lib64/X11 -lXext -lX11
LIB2 =	-L/usr/lib64/X11 -lXext -lX11 -lm -Llib/my/ -lmy -Llib/minilibx/  -lmlx ./lib/libson.so

all: $(NAME)

$(NAME): $(OBJ)
#	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) $(LIB) $(LIBMINI)
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(LIBMINI) $(LIB2)

clean:
	@rm -f $(OBJ)

fclean:		clean
	@rm -f $(NAME)

re: fclean all

