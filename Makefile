##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##


all:
	g++ -I./lib/includes test.cpp Irrlicht.cpp client.cpp -L./lib -lIrrlicht -L/usr/X11R6/lib64 -lGL -lXxf86vm -lXext -lX11 -lXcursor -lboost_timer -lpthread -lboost_system -g3

clean:

fclean:

re:			fclean all

.PHONY:		all clean fclean re core graphicals games
