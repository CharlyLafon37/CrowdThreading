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
void init_plateau(Cell plateau[][WINDOW_HEIGHT], int withSemaphore){
    int i, j;
    
    for(i = 0; i < WINDOW_WIDTH; i++)
    {
        for(j = 0; j < WINDOW_HEIGHT; j++)
        {
            plateau[i][j].occupe = 0;
			if(withSemaphore == 1)
            {
                sem_t sem;
                sem_init(&sem, 0, 1);
                plateau[i][j].verrou = sem;
            }
            else
                plateau[i][j].verrou = NULL;
        }
    }
	// Obstacles
	// Obstacle gauche
	for(i=XOBSTACLE_LEFT_TOP;i<XOBSTACLE_LEFT_TOP+OBSTACLE_WIDTH;i++){
		plateau[i][YOBSTACLE_LEFT_TOP].occupe=1;
		plateau[i][YOBSTACLE_LEFT_TOP+OBSTACLE_LEFT_HEIGHT-1].occupe=1;
		plateau[i][YOBSTACLE_LEFT_BOTTOM].occupe=1;
		plateau[i][YOBSTACLE_LEFT_BOTTOM+OBSTACLE_LEFT_HEIGHT-1].occupe=1;
	}
	for(i=0;i<OBSTACLE_LEFT_HEIGHT;i++){
		plateau[XOBSTACLE_LEFT_TOP][YOBSTACLE_LEFT_TOP+i].occupe=1;
		plateau[XOBSTACLE_LEFT_TOP+OBSTACLE_WIDTH][YOBSTACLE_LEFT_TOP+i].occupe=1;
		plateau[XOBSTACLE_LEFT_BOTTOM][YOBSTACLE_LEFT_BOTTOM+i].occupe=1;
		plateau[XOBSTACLE_LEFT_BOTTOM+OBSTACLE_WIDTH][YOBSTACLE_LEFT_BOTTOM+i].occupe=1;
	}
	// Obstacle droite
	for(i=XOBSTACLE_RIGHT_TOP;i<XOBSTACLE_RIGHT_TOP+OBSTACLE_WIDTH;i++){
		plateau[i][YOBSTACLE_RIGHT_TOP].occupe=1;
		plateau[i][YOBSTACLE_RIGHT_TOP+OBSTACLE_RIGHT_HEIGHT-1].occupe=1;
		plateau[i][YOBSTACLE_RIGHT_BOTTOM].occupe=1;
		plateau[i][YOBSTACLE_RIGHT_BOTTOM+OBSTACLE_RIGHT_HEIGHT-1].occupe=1;
	}
	for(i=0;i<OBSTACLE_RIGHT_HEIGHT;i++){
		plateau[XOBSTACLE_RIGHT_TOP][YOBSTACLE_RIGHT_TOP+i].occupe=1;
		plateau[XOBSTACLE_RIGHT_TOP+OBSTACLE_WIDTH][YOBSTACLE_RIGHT_TOP+i].occupe=1;
		plateau[XOBSTACLE_RIGHT_BOTTOM][YOBSTACLE_RIGHT_BOTTOM+i].occupe=1;
		plateau[XOBSTACLE_RIGHT_BOTTOM+OBSTACLE_WIDTH][YOBSTACLE_RIGHT_BOTTOM+i].occupe=1;
	}
}

void spawnPeople(Person people[], int nbPeople, Cell plateau[][WINDOW_HEIGHT])
{
    int i, j;
    srand(time(NULL));
    
    for(i = 0; i < nbPeople; i++)
    {
        randomizeAndPut(people, i, plateau);
    }
}

void randomizeAndPut(Person people[], int i, Cell plateau[][WINDOW_HEIGHT])
{
    int j, k;
    
    int randX = rand() % (XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
    int randY = rand() % (YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
    
    while(plateau[randX][randY].occupe == 1 || plateau[randX+PEOPLE_WIDTH-1][randY+PEOPLE_HEIGHT-1].occupe == 1
          || plateau[randX][randY+PEOPLE_HEIGHT-1].occupe == 1 || plateau[randX+PEOPLE_WIDTH-1][randY].occupe == 1)
    {
        randX = rand() % (XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
        randY = rand() % (YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
    }
    people[i].x = randX;
    people[i].y = randY;
    
    people[i].isArrived = 0;
    
    for(j = randX; j < randX + PEOPLE_WIDTH; j++)
    {
        for(k = randY;k < randY + PEOPLE_HEIGHT; k++)
        {
            plateau[j][k].occupe = 1;
        }
    }
}

/*
	Permet de détruire le sémaphore de chaque cellule du tableau.
*/
void destroy_tab_sem(Cell plateau[][WINDOW_HEIGHT]){

    int i, j;
    for(i = 0; i < WINDOW_WIDTH; i++)
    {
        for(j = 0; j < WINDOW_HEIGHT; j++)
        {
            sem_destroy(&(plateau[i][j].verrou));
        }
    }
}
