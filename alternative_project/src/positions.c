/*
	positions.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 
	Fonctions et procédures de calculs non graphique.
 */

#include <stdlib.h>
#include <time.h>
#include "positions.h"

void spawnPeople(Person people[], int nbPeople, Cell plateau[][WINDOW_HEIGHT])
{
    int i, j;
    srand(time(NULL));
    
    for(i = 0; i < WINDOW_WIDTH; i++)
    {
        for(j = 0; j < WINDOW_HEIGHT; j++)
        {
            plateau[i][j].occupe = 0;
	    //sem_t sem;
	    //sem_init(&sem, 1, 1);
	    //plateau[i][j].verrou = sem;
        }
    }
    
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
/*void destroy_tab_sem(Cell plateau[][WINDOW_HEIGHT]){

    int i=0,j=0;
    for(i = 0; i < WINDOW_WIDTH; i++)
    {
        for(j = 0; j < WINDOW_HEIGHT; j++)
        {
	    sem_destroy(&(plateau[i][j].verrou));
        }
    }
}*/
