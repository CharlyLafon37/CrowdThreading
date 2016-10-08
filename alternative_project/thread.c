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
#include "thread.h"
#include "positions.h"
#include "utils.h"


/**** -t2 ****/

void spawnPeopleThread(Person people[], int nbPeople, int *restant)
{
    int i,j,k;
    
    pthread_t threads[nbPeople];
    thread_person_data datas[nbPeople];
    
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
    
    printf("Personnes non sorties : %d\n",*restant);
    
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
        datas[i].n = i;
        datas[i].nbPeople = nbPeople;
        datas[i].people = people;
        
        printf("Creation du thread %d\n",i);
        if(pthread_create(&threads[i], NULL, thread_person, &datas[i]) == -1)
        {
            perror("pthread_create");
            return;
        }
    }
    
	// Attente des threads
	for(i = 0; i < nbPeople; i++)
    {
		if(pthread_join(threads[i], NULL))
        {
            perror("pthread_join");
            return;
        }
        (*restant)--;
        printf("Personnes non sorties : %d\n",*restant);
        printf("Thread %d terminé\n", i);
	}
}

void *thread_person(thread_person_data *arg)
{
    while(arg->people[arg->n].x!=XAZIMUTH || arg->people[arg->n].y!=YAZIMUTH)
    {
        Point newPosition = move_people(arg->n, arg->people, arg->nbPeople, XAZIMUTH, YAZIMUTH);
        
        arg->people[arg->n].x = newPosition.x;
        arg->people[arg->n].y = newPosition.y;
    }
    arg->people[arg->n].isArrived = 1;
    pthread_exit(NULL);
}


/**** -t1 ****/
















void spawnPeopleThreadSpace(Person people[], int nbPeople, int *restant)
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
    
    //Initialisation des tableaux
    pthread_t threads[NB_THREAD];
    thread_space_data datas[NB_THREAD];
    int tab_people[NB_THREAD][nbPeople];
    int tab_nbPeople[NB_THREAD];
    
    // On prépare les datas de chaque Thread
    for(i = 0; i < NB_THREAD; i++)
    {
        datas[i].n = i;
        datas[i].restant = restant;
        datas[i].nbPeople = nbPeople;
        datas[i].people = people;
        datas[i].nbPeopleSpace = tab_nbPeople;
        datas[i].peopleSpace = tab_people;
        datas[i].nbPeopleSpace[i] = tab_nbPeople[i];
        datas[i].peopleSpace[i] = tab_people[i];
        for(j = 0; j < nbPeople; j++)
        {
            datas[i].peopleSpace[i][j] = tab_people[i][j];
        }
        
        tab_nbPeople[i] = 0;
        printf("data tab %d = tab %d ; data tab i %d = tab i %d i %d\n",datas[i].peopleSpace,tab_people,datas[i].peopleSpace[i],tab_people[i],i);
    }
    
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
        int indice = indice_thread(randX,randY);
        datas[indice].peopleSpace[indice][datas[indice].nbPeopleSpace[indice]] = i;
        datas[indice].nbPeopleSpace[indice] = (datas[indice].nbPeopleSpace[indice]) + 1;
    }
    
    // Création des threads du terrain.
    for(i = 0; i < NB_THREAD; i++)
    {
        int j=0;
        printf("Creation du thread %d\n",i);
        if(pthread_create(&threads[i],NULL,thread_space,&datas[i])==-1)
        {
            perror("pthread_create");
            return;
        }
    }
    for(i = 0; i < NB_THREAD; i++)
    {
        if(pthread_join(threads[i],NULL))
        {
            perror("pthread_join");
            return;
        }
        printf("Thread %d terminé\n", i);
     }
}

void *thread_space(thread_space_data *arg){
    
    int i;
    int indice=arg->n;
    // Tant qu'il reste des personnes a traiter dans le thread
    while((*(arg->restant))>0)
    {
        // Boucle de traitement des personnes
        for(i = 0; i < arg->nbPeopleSpace[indice]; i++)
        {
            int index = arg->peopleSpace[indice][i];
            if((arg->people[index].x != XAZIMUTH || arg->people[index].y != YAZIMUTH) && index!=-1)
            {
                Point newPosition = move_people(index, arg->people, arg->nbPeople, XAZIMUTH, YAZIMUTH);
                arg->people[index].x = newPosition.x;
                arg->people[index].y = newPosition.y;
                if(arg->people[index].x == XAZIMUTH && arg->people[index].y == YAZIMUTH)
                {
                    arg->people[index].isArrived = 1;
                    (*(arg->restant))--;
                    printf("thread %d rest %d\n",indice,*(arg->restant));
                }
                int newIndex = indice_thread(newPosition.x, newPosition.y);
                if(newIndex != indice)
                {
                    // Garder en mémoire l'index de la personne
                    int temp=arg->peopleSpace[indice][i];
                    printf("thread %d newIndex %d\n",indice,newIndex);
                    
                    // Ajouter l'index de la personne sur le nouveau tableau
                    arg->peopleSpace[newIndex][arg->nbPeopleSpace[newIndex]] = temp;
                    arg->nbPeopleSpace[newIndex] = arg->nbPeopleSpace[newIndex]+1;
                    
                    // Supprimer l'index du tableau 1
                    int k=0;
                    for(k=i;k<(arg->nbPeopleSpace[indice])-1;k++)
                    {
                        arg->peopleSpace[indice][k] = arg->peopleSpace[indice][k+1];
                    }
                    arg->peopleSpace[indice][--arg->nbPeopleSpace[indice]] = -1;
                }
            }
        }
    }
}




