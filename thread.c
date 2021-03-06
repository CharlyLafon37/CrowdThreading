/*
	thread.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
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
    
    while(arg->people[arg->n].position.x!=XAZIMUTH || arg->people[arg->n].position.y!=YAZIMUTH)
    {
        SDL_Point newPosition = move_people(arg->n, arg->people, arg->nbPeople, XAZIMUTH, YAZIMUTH);
        
        arg->people[arg->n].position.x = newPosition.x;
        arg->people[arg->n].position.y = newPosition.y;
        SDL_Delay(20);
    }
    arg->people[arg->n].isArrived = 1;
    (*(arg->restant))--;
    printf("rest %d\n",*(arg->restant));
    pthread_exit(NULL);
    
}

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
    
    pthread_t threads[NB_THREAD];
    thread_space_data datas[NB_THREAD];
	int tab_people[NB_THREAD][nbPeople];
	int tab_nbPeople[NB_THREAD];
	//Initialisation des tableaux

	// On prépare les datas de chaque Thread
	for(i=0;i<NB_THREAD;i++){
		datas[i].n=i;
		datas[i].restant=restant;
		datas[i].nbPeople=nbPeople;
		datas[i].people=people;
		datas[i].nbPeopleSpace=tab_nbPeople;
		datas[i].peopleSpace=tab_people;
		datas[i].nbPeopleSpace[i]=tab_nbPeople[i];
		datas[i].peopleSpace[i]=tab_people[i];
		for(j=0;j<nbPeople;j++)
			datas[i].peopleSpace[i][j]=tab_people[i][j];
		tab_nbPeople[i]=0;
		printf("data tab %d = tab %d ; data tab i %d = tab i %d i %d\n",datas[i].peopleSpace,tab_people,datas[i].peopleSpace[i],tab_people[i],i);
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
		int indice = indice_thread(randX,randY);
		datas[indice].peopleSpace[indice][datas[indice].nbPeopleSpace[indice]]=i;
		datas[indice].nbPeopleSpace[indice]=(datas[indice].nbPeopleSpace[indice])+1;
    }

	// Création des threads du terrain.
	for(i=0;i<NB_THREAD;i++){
		int j=0;
		printf("creation du thread %d\n",i);
		if(pthread_create(&threads[i],NULL,thread_space,&datas[i])==-1){
		    perror("pthread_create");
		    return;
		}
	}
	/*for(i=0;i<NB_THREAD;i++){
		if(pthread_join(threads[i],NULL)){
				perror("pthread_join");
				return;
		}
		printf("apres creation du thread %d\n",i);
	}*/
}

void *thread_space(thread_space_data *arg){
    
    int i;
	int indice=arg->n;//printf("indice %d restant %d\n",indice,(*(arg->restant)));
    // Tant qu'il reste des personnes a traiter dans le thread
	while((*(arg->restant))>0){
		SDL_Delay(20);
		// Boucle de traitement des personnes
		for(i=0;i<arg->nbPeopleSpace[indice];i++){
			int index=arg->peopleSpace[indice][i];
			if((arg->people[index].position.x!=XAZIMUTH || arg->people[index].position.y!=YAZIMUTH) && index!=-1){
				SDL_Point newPosition = move_people(index, arg->people, arg->nbPeople, XAZIMUTH, YAZIMUTH);
		    	arg->people[index].position.x = newPosition.x;
		    	arg->people[index].position.y = newPosition.y;
				if(arg->people[index].position.x==XAZIMUTH && arg->people[index].position.y==YAZIMUTH){
					arg->people[index].isArrived = 1;
    				(*(arg->restant))--;
    				printf("thread %d rest %d\n",indice,*(arg->restant));
				}
				int newIndex=indice_thread(newPosition.x, newPosition.y);
				if(newIndex!=indice){//printf("lol\n");
					/*move_index_people(arg->nbPeopleSpace[indice], arg->nbPeopleSpace[newIndex],
					arg->peopleSpace[indice], arg->peopleSpace[newIndex], i);printf("lal\n");*/
					// Garder en mémoire l'index de la personne
					int temp=arg->peopleSpace[indice][i];
					printf("thread %d newIndex %d\n",indice,newIndex);
					
					// Ajouter l'index de la personne sur le nouveau tableau
					arg->peopleSpace[newIndex][arg->nbPeopleSpace[newIndex]]=temp;
					arg->nbPeopleSpace[newIndex]=arg->nbPeopleSpace[newIndex]+1;

					// Supprimer l'index du tableau 1
					int k=0;
					for(k=i;k<(arg->nbPeopleSpace[indice])-1;k++){
						arg->peopleSpace[indice][k]=arg->peopleSpace[indice][k+1];
					}
					arg->peopleSpace[indice][--arg->nbPeopleSpace[indice]]=-1;
				}
			}
		}
	}

}




