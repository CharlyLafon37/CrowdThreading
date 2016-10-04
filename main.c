#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "positions.h"
#include "utils.h"

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople);
void print(SDL_Renderer* renderer, SDL_Rect obstacles[], SDL_Rect people[], int nbPeople);

int option_thread=0;

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
    SDL_Rect people[nbPeople];
    
    obstaclesLayout(obstacles);
    spawnPeople(people, nbPeople);
    
    print(renderer, obstacles, people, nbPeople);
    
    /****/
    int i, j;
    for(i = 0; i < 100; i++)
    {
        for(j = 0; j < nbPeople; j++)
        {
            SDL_Point newPosition = move_people(j, people, nbPeople, XAZIMUTH, YAZIMUTH);
            
            people[j].x = newPosition.x;
            people[j].y = newPosition.y;
            printf("%d  ", people[j].x);
            printf("%d\n", people[j].y);
        }
        print(renderer, obstacles, people, nbPeople);
        SDL_Delay(100);
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
            }else if(argv[i][1] == 't'){
                if(argv[i][2] == '0'){
                    option_thread=0;
                }else if(argv[i][2] == '1'){
                    option_thread=1;
                }else if(argv[i][2] == '2'){
                    option_thread=2;
                }
            }
        }
    }
}

void print(SDL_Renderer* renderer, SDL_Rect obstacles[], SDL_Rect people[], int nbPeople)
{
    /**** Background drawing ****/
    SDL_SetRenderDrawColor(renderer, 175, 175, 175, 255); // Background = grey
    SDL_RenderClear(renderer);
    
    /**** Obstacles drawing ****/
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Rectangles = black
    SDL_RenderFillRects(renderer, obstacles, 4);
    
    /**** People drawing ****/
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // People = red
    SDL_RenderFillRects(renderer, people, nbPeople);
    
    SDL_RenderPresent(renderer); // Rendering on screen
}
