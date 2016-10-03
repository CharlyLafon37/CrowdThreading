/*
	positions.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include "positions.h"
#include <time.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 128
#define DEFAULT_NBPEOPLE 16
#define PEOPLE_WIDTH 4
#define PEOPLE_HEIGHT 4
#define XMIN_PEOPLE 129
#define YMIN_PEOPLE 0
#define XMAX_PEOPLE WINDOW_WIDTH-PEOPLE_WIDTH
#define YMAX_PEOPLE WINDOW_HEIGHT-PEOPLE_HEIGHT


void obstaclesLayout(SDL_Rect obstacles[])
{
    obstacles[0].w = 16; obstacles[0].h = 60; obstacles[0].x = 0; obstacles[0].y = 0;
    obstacles[1].w = 16; obstacles[1].h = 60; obstacles[1].x = 0; obstacles[1].y = WINDOW_HEIGHT - obstacles[1].h;
    obstacles[2].w = 16; obstacles[2].h = 56; obstacles[2].x = 128 - obstacles[2].w; obstacles[2].y = 0;
    obstacles[3].w = 16; obstacles[3].h = 56; obstacles[3].x = 128 - obstacles[3].w; obstacles[3].y = WINDOW_HEIGHT - obstacles[3].h;
}

void spawnPeople(SDL_Rect people[], int nbPeople)
{
    int i;
    srand(time(NULL));
    
    for(i = 0; i < nbPeople; i++)
    {
        people[i].w = PEOPLE_WIDTH;
        people[i].h = PEOPLE_HEIGHT;
        people[i].x = rand()%(XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
        people[i].y = rand()%(YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
    }
}
