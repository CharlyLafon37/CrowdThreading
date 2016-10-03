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
#define DEFAULT_NBPEOPLE 16
#define PEOPLE_WIDTH 4
#define PEOPLE_HEIGHT 4
#define XMIN_PEOPLE 129
#define YMIN_PEOPLE 0
#define XMAX_PEOPLE WINDOW_WIDTH-PEOPLE_WIDTH
#define YMAX_PEOPLE WINDOW_HEIGHT-PEOPLE_HEIGHT

void obstaclesLayout(SDL_Rect obstacles[]);
void spawnPeople(SDL_Rect people[], int nbPeople);

#endif
