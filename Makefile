##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##


all:	
	g++ -I./lib/includes test.cpp -L./lib -lIrrlicht -L/usr/X11R6/lib64 -lGL -lXxf86vm -lXext -lX11 -lXcursor

clean:

fclean:

re:			fclean all

.PHONY:		all clean fclean re core graphicals games
