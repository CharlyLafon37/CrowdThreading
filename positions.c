/*
	positions.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "positions.h"

void obstaclesLayout(SDL_Rect obstacles[])
{
    obstacles[0].w = OBSTACLE_WIDTH; obstacles[0].h = OBSTACLE_LEFT_HEIGHT; obstacles[0].x = XOBSTACLE_LEFT_TOP; obstacles[0].y = YOBSTACLE_LEFT_TOP;
    obstacles[1].w = OBSTACLE_WIDTH; obstacles[1].h = OBSTACLE_LEFT_HEIGHT; obstacles[1].x = XOBSTACLE_LEFT_BOTTOM; obstacles[1].y = YOBSTACLE_LEFT_BOTTOM;
    obstacles[2].w = OBSTACLE_WIDTH; obstacles[2].h = OBSTACLE_RIGHT_HEIGHT; obstacles[2].x = XOBSTACLE_RIGHT_TOP; obstacles[2].y = YOBSTACLE_RIGHT_TOP;
    obstacles[3].w = OBSTACLE_WIDTH; obstacles[3].h = OBSTACLE_RIGHT_HEIGHT; obstacles[3].x = XOBSTACLE_RIGHT_BOTTOM; obstacles[3].y = YOBSTACLE_RIGHT_BOTTOM;
}

void spawnPeople(Person people[], int nbPeople)
{
    int i,j,k;
    srand(time(NULL));

    // Initialisation du plateau pour verifier la position des personnes.
    int plateau[WINDOW_WIDTH][WINDOW_HEIGHT];
    for(i=0;i<WINDOW_WIDTH;i++)
    {
        for(j=0;j<WINDOW_HEIGHT;j++)
        {
            plateau[i][j]=0;
        }
    }
   
    for(i = 0; i < nbPeople; i++)
    {
        people[i].position.w = PEOPLE_WIDTH;
        people[i].position.h = PEOPLE_HEIGHT;
        
        int randX=rand()%(XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
        int randY=rand()%(YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
        while(plateau[randX][randY]==1 || plateau[randX+PEOPLE_WIDTH-1][randY+PEOPLE_HEIGHT-1]==1
              ||plateau[randX][randY+PEOPLE_HEIGHT-1]==1 || plateau[randX+PEOPLE_WIDTH-1][randY]==1)
        {
            randX=rand()%(XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
            randY=rand()%(YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
        }
        people[i].position.x = randX;
        people[i].position.y = randY;
        
        people[i].isArrived = 0;
        
        for(j=randX;j<randX+PEOPLE_WIDTH;j++)
        {
            for(k=randY;k<randY+PEOPLE_HEIGHT;k++)
            {
                plateau[j][k]=1;
            }
        }
    }
}
