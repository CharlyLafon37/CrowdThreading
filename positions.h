/*
	positions.h
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/


#ifndef POSITIONS
#define POSITIONS

#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 128

#define OBSTACLE_WIDTH 16
#define OBSTACLE_LEFT_HEIGHT 60
#define OBSTACLE_RIGHT_HEIGHT 56
#define XOBSTACLE_LEFT_TOP 0
#define YOBSTACLE_LEFT_TOP 0
#define XOBSTACLE_LEFT_BOTTOM 0
#define YOBSTACLE_LEFT_BOTTOM WINDOW_HEIGHT-OBSTACLE_LEFT_HEIGHT
#define XOBSTACLE_RIGHT_TOP 128-OBSTACLE_WIDTH
#define YOBSTACLE_RIGHT_TOP 0
#define XOBSTACLE_RIGHT_BOTTOM 128-OBSTACLE_WIDTH
#define YOBSTACLE_RIGHT_BOTTOM  WINDOW_HEIGHT-OBSTACLE_RIGHT_HEIGHT

#define DEFAULT_NBPEOPLE 16
#define PEOPLE_WIDTH 4
#define PEOPLE_HEIGHT 4
#define XMIN_PEOPLE 129
#define YMIN_PEOPLE 0
#define XMAX_PEOPLE WINDOW_WIDTH-PEOPLE_WIDTH
#define YMAX_PEOPLE WINDOW_HEIGHT-PEOPLE_HEIGHT

#define XAZIMUTH 0
#define YAZIMUTH 60

void obstaclesLayout(SDL_Rect obstacles[]);
void spawnPeople(SDL_Rect people[], int nbPeople);

#endif
