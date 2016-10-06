#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "positions.h"
#include "utils.h"
#include "main.h"

int option_thread=0;
int iterations=500;

int main(int argc, char** argv)
{
    /**** Arguments handling ****/
    int nbPeople = DEFAULT_NBPEOPLE;
    
    if(argc != 1)
        argumentsTreatment(argv, argc-1, &nbPeople);
    
    /**** Initialisation of SDL structures ****/
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    if (SDL_VideoInit(NULL) < 0)
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    
    window = SDL_CreateWindow("CrowdThreading",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH,
                               WINDOW_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if(!window)
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return -1;
    }
    
    renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    
    /**** Initialisation of entities' position ****/
    SDL_Rect obstacles[4];
    Person people[nbPeople];
    
    obstaclesLayout(obstacles);

    if(option_thread==0) // Si on simule sur 1 seul thread.
    {
	    spawnPeople(people, nbPeople);
	    
	    print(renderer, obstacles, people, nbPeople);
        
	    int i, j;
	    for(i = 0; i < iterations; i++)
	    {
            for(j = 0; j < nbPeople; j++)
            {
                SDL_Point newPosition = move_people(j, people, nbPeople, XAZIMUTH, YAZIMUTH);
		    
                people[j].person.x = newPosition.x;
                people[j].person.y = newPosition.y;
                
                if(people[j].person.x == XAZIMUTH && people[j].person.y == YAZIMUTH)
                    people[j].isArrived = 1;
            }
            print(renderer, obstacles, people, nbPeople);
            SDL_Delay(30);
	    }
    }
    else if(option_thread==1) // Si on simule en divisant le terrain en 4 thread.
    {
		
    }
    else if(option_thread==2) // Si on simule avec un thread par personne.
    {
		spawnPeopleThread(people, nbPeople); // Création des personnes et de leur thread.

		int i;
		for(i=0;i<2*iterations;i++)
        {
			print(renderer, obstacles, people, nbPeople); // Rendu graphique
		}
    }

    SDL_Delay(5000); // Attendre cinq secondes, que l'utilisateur voie la fenêtre
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    
    return 0;
}

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople)
{
    int i;
    for(i = 1; i <= nbArguments; i++) // Begins to 1 because first argument = name of executable
    {
        if(argv[i][0] == '-')
        {
            if(argv[i][1] == 'p')
            {
                char temp[2];
                temp[0] = argv[i][2];
                *nbPeople = pow(2, atoi(temp));
            }
            else if(argv[i][1] == 't')
            {
                if(argv[i][2] == '0')
                    option_thread=0;
                else if(argv[i][2] == '1')
                    option_thread=1;
                else if(argv[i][2] == '2')
                    option_thread=2;
            }
        }
    }
}

void print(SDL_Renderer* renderer, SDL_Rect obstacles[], Person people[], int nbPeople)
{
    /**** Background drawing ****/
    SDL_SetRenderDrawColor(renderer, 175, 175, 175, 255); // Background = grey
    SDL_RenderClear(renderer);
    
    /**** Obstacles drawing ****/
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Rectangles = black
    SDL_RenderFillRects(renderer, obstacles, 4);
    
    /**** People drawing ****/
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // People = red
    
    int i;
    for(i = 0; i < nbPeople; i++)
    {
        SDL_RenderFillRect(renderer, &(people[i].person));
    }
    
    SDL_RenderPresent(renderer); // Rendering on screen
}


void spawnPeopleThread(Person people[], int nbPeople)
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
        people[i].person.w = PEOPLE_WIDTH;
        people[i].person.h = PEOPLE_HEIGHT;
        
        int randX=rand()%(XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
        int randY=rand()%(YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;

        while(plateau[randX][randY]==1 || plateau[randX+PEOPLE_WIDTH-1][randY+PEOPLE_HEIGHT-1]==1
              ||plateau[randX][randY+PEOPLE_HEIGHT-1]==1 || plateau[randX+PEOPLE_WIDTH-1][randY]==1)
        {
            randX=rand()%(XMAX_PEOPLE-XMIN_PEOPLE) + XMIN_PEOPLE;
            randY=rand()%(YMAX_PEOPLE-YMIN_PEOPLE) + YMIN_PEOPLE;
        }
        people[i].person.x = randX;
        people[i].person.y = randY;
        
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
		datas[i].nbPeople=nbPeople;
		datas[i].people=people;
		printf("creation du thread %d\n",i);
		if(pthread_create(&threads[i],NULL,thread_person,&datas[i])==-1){
			perror("pthread_create");
			return;
		}
		if(pthread_join(threads[i],NULL)){
			perror("pthread_join");
			return;
		}
		printf("apres creation du thread %d\n",i);
    }
}

void *thread_person(thread_person_data *arg){

	int i;
	printf("Debut du thread de la personne %d\n",arg->n);

	for(i=0;i<iterations;i++)
    {
		SDL_Point newPosition = move_people(arg->n, arg->people, arg->nbPeople, XAZIMUTH, YAZIMUTH);
				
		arg->people[arg->n].person.x = newPosition.x;
		arg->people[arg->n].person.y = newPosition.y;
		SDL_Delay(20);
	}
	pthread_exit(NULL);

}




