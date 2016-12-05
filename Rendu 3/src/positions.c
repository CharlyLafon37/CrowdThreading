/*
	positions.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 
	Fonctions et procédures de calculs non graphique.
 */

#include <stdlib.h>
#include <time.h>
#include "positions.h"

/*
	Place les obstacles sur la tableau, passe à 0 toutes les cases vides et créé les sémaphores.
*/
void init_plateau(int plateau[][WINDOW_HEIGHT])
{
    int i, j;
    
    for(i = 0; i < WINDOW_WIDTH; i++)
    {
        for(j = 0; j < WINDOW_HEIGHT; j++)
        {
            plateau[i][j] = 0;
        }
    }

	// Obstacle gauche
	for(i=XOBSTACLE_LEFT_TOP;i<XOBSTACLE_LEFT_TOP+OBSTACLE_WIDTH;i++){
		plateau[i][YOBSTACLE_LEFT_TOP] = 1;
		plateau[i][YOBSTACLE_LEFT_TOP+OBSTACLE_LEFT_HEIGHT-1] = 1;
		plateau[i][YOBSTACLE_LEFT_BOTTOM] = 1;
		plateau[i][YOBSTACLE_LEFT_BOTTOM+OBSTACLE_LEFT_HEIGHT-1] = 1;
	}
	for(i=0;i<OBSTACLE_LEFT_HEIGHT;i++){
		plateau[XOBSTACLE_LEFT_TOP][YOBSTACLE_LEFT_TOP+i] = 1;
		plateau[XOBSTACLE_LEFT_TOP+OBSTACLE_WIDTH][YOBSTACLE_LEFT_TOP+i] = 1;
		plateau[XOBSTACLE_LEFT_BOTTOM][YOBSTACLE_LEFT_BOTTOM+i] = 1;
		plateau[XOBSTACLE_LEFT_BOTTOM+OBSTACLE_WIDTH][YOBSTACLE_LEFT_BOTTOM+i] = 1;
	}
	// Obstacle droite
	for(i=XOBSTACLE_RIGHT_TOP;i<XOBSTACLE_RIGHT_TOP+OBSTACLE_WIDTH;i++){
		plateau[i][YOBSTACLE_RIGHT_TOP] = 1;
		plateau[i][YOBSTACLE_RIGHT_TOP+OBSTACLE_RIGHT_HEIGHT-1] = 1;
		plateau[i][YOBSTACLE_RIGHT_BOTTOM] = 1;
		plateau[i][YOBSTACLE_RIGHT_BOTTOM+OBSTACLE_RIGHT_HEIGHT-1] = 1;
	}
	for(i=0;i<OBSTACLE_RIGHT_HEIGHT;i++){
		plateau[XOBSTACLE_RIGHT_TOP][YOBSTACLE_RIGHT_TOP+i] = 1;
		plateau[XOBSTACLE_RIGHT_TOP+OBSTACLE_WIDTH][YOBSTACLE_RIGHT_TOP+i] = 1;
		plateau[XOBSTACLE_RIGHT_BOTTOM][YOBSTACLE_RIGHT_BOTTOM+i] = 1;
		plateau[XOBSTACLE_RIGHT_BOTTOM+OBSTACLE_WIDTH][YOBSTACLE_RIGHT_BOTTOM+i] = 1;
	}
}

void spawnPeople(Person people[], int nbPeople, int plateau[][WINDOW_HEIGHT])
{
    int i, j;
    srand(time(NULL));
    
    for(i = 0; i < nbPeople; i++)
    {
        randomizeAndPut(people, i, plateau);
    }
}

void randomizeAndPut(Person people[], int i, int plateau[][WINDOW_HEIGHT])
{
    int j, k;
    
    int randX = rand() % (XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
    int randY = rand() % (YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
    
    while(plateau[randX][randY] == 1 || plateau[randX+PEOPLE_WIDTH-1][randY+PEOPLE_HEIGHT-1] == 1
          || plateau[randX][randY+PEOPLE_HEIGHT-1] == 1 || plateau[randX+PEOPLE_WIDTH-1][randY] == 1)
    {
        randX = rand() % (XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
        randY = rand() % (YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
    }
    people[i].x = randX;
    people[i].y = randY;
    
    people[i].isArrived = 0;
    
    for(j = randX; j < randX + PEOPLE_WIDTH; j++)
    {
        for(k = randY; k < randY + PEOPLE_HEIGHT; k++)
        {
            plateau[j][k] = 1;
        }
    }
}
