#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "positions.h"
#include "utils.h"
#include "thread.h"

int main(int argc, char** argv)
{
    /**** Arguments handling ****/
    int nbPeople = DEFAULT_NBPEOPLE;
    int option_thread = DEFAULT_THREAD;
    int option_mesure = DEFAULT_MESURE;
    
    if(argc != 1)
        argumentsTreatment(argv, argc-1, &nbPeople, &option_thread, &option_mesure);
    
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
    
	int restant = nbPeople;

    if(option_thread == 0) // Si on simule sur 1 seul thread.
    {
	    spawnPeople(people, nbPeople);
	    
	    print(renderer, obstacles, people, nbPeople);
        
        int i;
	    while(restant > 0)
	    {
            for(i = 0; i < nbPeople; i++)
            {
                SDL_Point newPosition = move_people(i, people, nbPeople, XAZIMUTH, YAZIMUTH);
		    
                people[i].position.x = newPosition.x;
                people[i].position.y = newPosition.y;
                
                if(people[i].position.x == XAZIMUTH && people[i].position.y == YAZIMUTH && people[i].isArrived == 0)
                {
                    people[i].isArrived = 1;
					restant--;
				}
            }
            print(renderer, obstacles, people, nbPeople);
            SDL_Delay(30);
	    }
    }
    else if(option_thread == 1) // Si on simule en divisant le terrain en 4 thread.
    {
		spawnPeopleThreadSpace(people, nbPeople, &restant); // Création des personnes et de leur thread.

		int i;
		while(i<300 && restant>0)
        {
            i++;SDL_Delay(50);
			print(renderer, obstacles, people, nbPeople); // Rendu graphique
		}
    }
    else if(option_thread == 2) // Si on simule avec un thread par personne.
    {
		spawnPeopleThread(people, nbPeople, &restant); // Création des personnes et de leur thread.

		int i;
		while(i<300 && restant>0)
        {
            i++;SDL_Delay(50);
			print(renderer, obstacles, people, nbPeople); // Rendu graphique
		}
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    
    return 0;
}

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople, int* option_thread, int* option_mesure)
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
                if(argv[i][2] == '0') *option_thread=0;
                else if(argv[i][2] == '1') *option_thread=1;
                else if(argv[i][2] == '2') *option_thread=2;
            }
            else if(argv[i][1] == 'm')
            {
                *option_mesure = 1;
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
        SDL_RenderFillRect(renderer, &(people[i].position));
    }
    
    SDL_RenderPresent(renderer); // Rendering on screen
}
