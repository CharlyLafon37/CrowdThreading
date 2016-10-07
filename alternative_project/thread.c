/*
	thread.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "thread.h"
#include "positions.h"
#include "utils.h"

void spawnPeopleThread(Person people[], int nbPeople, int *restant)
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
    
    pthread_t threads[nbPeople];
    thread_person_data datas[nbPeople];
    
    for(i = 0; i < nbPeople; i++)
    {
        int randX=rand()%(XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
        int randY=rand()%(YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
        
        while(plateau[randX][randY]==1 || plateau[randX+PEOPLE_WIDTH-1][randY+PEOPLE_HEIGHT-1]==1
              ||plateau[randX][randY+PEOPLE_HEIGHT-1]==1 || plateau[randX+PEOPLE_WIDTH-1][randY]==1)
        {
            randX=rand()%(XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
            randY=rand()%(YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
        }
        people[i].x = randX;
        people[i].y = randY;
        
        people[i].isArrived = 0;
        
        for(j=randX;j<randX+PEOPLE_WIDTH;j++)
        {
            for(k=randY;k<randY+PEOPLE_HEIGHT;k++)
            {
                plateau[j][k]=1;
            }
        }
        // Création du thread de la personne.
        datas[i].n=i;
        datas[i].restant=restant;
        datas[i].nbPeople=nbPeople;
        datas[i].people=people;
        printf("creation du thread %d\n",i);
        if(pthread_create(&threads[i],NULL,thread_person,&datas[i])==-1){
            perror("pthread_create");
            return;
        }
        /*if(pthread_join(threads[i],NULL)){
            perror("pthread_join");
            return;
        }
        printf("apres creation du thread %d\n",i);*/
    }
}

void *thread_person(thread_person_data *arg){
    
    int i;
    printf("Debut du thread de la personne %d\n",arg->n);
    
    while(arg->people[arg->n].x!=XAZIMUTH || arg->people[arg->n].y!=YAZIMUTH)
    {
        Point newPosition = move_people(arg->n, arg->people, arg->nbPeople, XAZIMUTH, YAZIMUTH);
        
        arg->people[arg->n].x = newPosition.x;
        arg->people[arg->n].y = newPosition.y;
        usleep(20000);
    }
    arg->people[arg->n].isArrived = 1;
    (*(arg->restant))--;
    printf("rest %d\n",*(arg->restant));
    pthread_exit(NULL);
    
}
