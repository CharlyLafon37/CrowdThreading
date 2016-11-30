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

void spawnPeopleThread(Person people[], int nbPeople, int *restant, int option_mesure, int plateau[][WINDOW_HEIGHT], sem_t* sem_plateau)
{
    int i, j;
    
    pthread_t* threads = malloc(nbPeople * sizeof(pthread_t));
    thread_person_data* datas = malloc(nbPeople * sizeof(thread_person_data));
    
    srand(time(NULL));
    
    if(option_mesure == 0)
        printf("Personnes non sorties : %d\n",*restant);
    
    //Semaphores permettant l'attente des threads filles
    sem_t* sem = malloc(nbPeople * sizeof(sem_t));
    
    for(i = 0; i < nbPeople; i++)
    {
        sem_init(&(sem[i]), 0, 0);
        
        randomizeAndPut(people, i, plateau);
        
        // Création du thread de la personne.
        datas[i].n = i;
        datas[i].nbPeople = nbPeople;
        datas[i].people = people;
        datas[i].plateau = plateau;
        datas[i].sem_plateau = sem_plateau;
        datas[i].sem_join = &(sem[i]);
        
        if(option_mesure == 0)
            printf("Creation du thread %d\n",i);
        if(pthread_create(&threads[i], NULL, thread_person, &datas[i]) == -1)
        {
            perror("pthread_create");
            return;
        }
    }
    
    // Attente des threads filles
    for(i = 0; i < nbPeople; i++)
    {
        sem_wait(&(sem[i]));
        (*restant)--;
        if(option_mesure == 0)
        {
            printf("Personnes non sorties : %d\n",*restant);
            printf("Thread %d terminé\n", i);
        }
        sem_destroy(&(sem[i]));
    }
                                       
    free(sem);
    free(threads);
    free(datas);
}

void *thread_person(thread_person_data *arg)
{
    while(arg->people[arg->n].x!=XAZIMUTH || arg->people[arg->n].y!=YAZIMUTH)
    {
        Point newPosition = move_people(arg->n, arg->people, arg->nbPeople, XAZIMUTH, YAZIMUTH, *(arg->plateau), arg->sem_plateau);
    }
    arg->people[arg->n].isArrived = 1;
    sem_post(arg->sem_join);
    pthread_exit(NULL);
}



/**** -t1 ****/


void spawnPeopleThreadSpace(Person people[], int nbPeople, int *restant, int option_mesure, int plateau[][WINDOW_HEIGHT], sem_t* sem_plateau)
{
    int i,j,k;
    srand(time(NULL));
    
    if(option_mesure == 0)
        printf("Personnes non sorties : %d\n", *restant);
    
    pthread_t threads[NB_THREAD];
    thread_space_data datas[NB_THREAD];
    
    //Semaphores permettant l'attente des threads filles
    sem_t sem[NB_THREAD];

	// On prépare les datas de chaque Thread
	for(i=0;i<NB_THREAD;i++)
    {
        sem_init(&(sem[i]), 0, 0);
        
		datas[i].n=i;
		datas[i].restant=restant;
		datas[i].nbPeople=nbPeople;
		datas[i].people=people;
		datas[i].nbPeopleSpace=0;
		datas[i].peopleSpace=malloc(sizeof(int) * nbPeople);
		datas[i].datas=datas;
		datas[i].option_mesure = option_mesure;
        sem_init(&(datas[i].sem_space), 0, 1);
		if(sem_plateau!=NULL){
        	datas[i].use_sem=1;
		}else{
			datas[i].use_sem=0;
		}
		datas[i].plateau = plateau;
        datas[i].sem_join = &(sem[i]);
	}
    
    for(i = 0; i < nbPeople; i++)
    {
        int randX=rand()%(XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
        int randY=rand()%(YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
        
        while(plateau[randX][randY] == 1 || plateau[randX+PEOPLE_WIDTH-1][randY+PEOPLE_HEIGHT-1] == 1
              ||plateau[randX][randY+PEOPLE_HEIGHT-1] == 1 || plateau[randX+PEOPLE_WIDTH-1][randY] == 1)
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
                plateau[j][k] = 1;
            }
        }
        
		int indice = indice_thread(randX,randY);
		datas[indice].peopleSpace[datas[indice].nbPeopleSpace]=i;
		datas[indice].nbPeopleSpace=(datas[indice].nbPeopleSpace)+1;
    }

	// Création des threads du terrain.
	for(i = 0; i < NB_THREAD; i++)
    {
		int j=0;
        if(option_mesure == 0)
            printf("Creation du thread %d\n",i);
		if(pthread_create(&threads[i], NULL, thread_space, &datas[i]) == -1)
        {
		    perror("pthread_create");
		    return;
		}
	}
    
    // Attente des threads filles
	for(i = 0; i < NB_THREAD; i++)
    {
        sem_wait(&(sem[i]));
        if(option_mesure == 0)
            printf("Thread %d terminé\n", i);
        sem_destroy(&(sem[i]));
		sem_destroy(&(datas[i].sem_space));
    }
}

void *thread_space(thread_space_data *arg)
{
    int i,peopleLeft=0;
	int indice=arg->n;

    sem_t* next_sem;
	sem_t* sem;
	if(arg->use_sem!=0 && indice>=0){
		sem=&(arg->sem_space);
		if(indice>0)
			next_sem=&((arg->datas[indice-1]).sem_space);
		else
			next_sem=NULL;
    }else{
	    next_sem=NULL;
        sem=NULL;
    }

    // Tant qu'il reste des personnes a traiter dans le thread
	while((*(arg->restant))>0)
    {
		// Boucle de traitement des personnes
		for(i=0;i<arg->nbPeopleSpace;i++)
        {
			if(sem!=NULL)
				sem_wait(sem);
            
			int index=arg->peopleSpace[i];
			if(arg->people[index].x!=XAZIMUTH || arg->people[index].y!=YAZIMUTH)
            {
				Point newPosition = move_people_space(index, arg->people, arg->nbPeople, XAZIMUTH, YAZIMUTH, *(arg->plateau), sem, next_sem,indice);
				int newIndex=indice_thread(newPosition.x, newPosition.y);
				// Si la personne est sortie
				if(arg->people[index].x==XAZIMUTH && arg->people[index].y==YAZIMUTH)
                {
					arg->people[index].isArrived = 1;
    				(*(arg->restant))--;
                    if(arg->option_mesure == 0)
                        printf("Personnes non sorties : %d\n",*(arg->restant));
					peopleLeft++;
				}
				// Si la personne n'est plus dans le meme espace
                else if(newIndex!=indice)
                {
                    // Garder en mémoire l'index de la personne
                    int temp=arg->peopleSpace[i];
                    
                    // Ajouter l'index de la personne sur le nouveau tableau
                    (arg->datas[newIndex]).peopleSpace[(arg->datas[newIndex]).nbPeopleSpace] = temp;
                    (arg->datas[newIndex]).nbPeopleSpace=((arg->datas[newIndex]).nbPeopleSpace)+1;
                    
                    // Supprimer l'index du tableau 1
                    int k=0;
                    for(k=i;k<(arg->nbPeopleSpace)-1;k++)
                    {
                        arg->peopleSpace[k] = arg->peopleSpace[k+1];
                    }
					arg->nbPeopleSpace = (arg->nbPeopleSpace) - 1;
                    arg->peopleSpace[(arg->nbPeopleSpace)] = -1;
					// On deverouille le thread adjacent
					if(next_sem!=NULL){
						sem_post(next_sem);
					}
                }
			}
			// On deverouille notre thread
			if(sem!=NULL)
				sem_post(sem);
		}
	}
	free(arg->peopleSpace);
    sem_post(arg->sem_join);
	pthread_exit(NULL);
}




