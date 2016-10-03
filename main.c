#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "positions.h"

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 128
#define DEFAULT_NBPEOPLE 16
#define PEOPLE_WIDTH 4
#define PEOPLE_HEIGHT 4
#define XMIN_PEOPLE 129
#define YMIN_PEOPLE 0
#define XMAX_PEOPLE WINDOW_WIDTH-PEOPLE_WIDTH
#define YMAX_PEOPLE WINDOW_HEIGHT-PEOPLE_HEIGHT


void argumentsTreatment(char** argv, int nbArguments, int* nbPeople);
void print(SDL_Renderer* renderer, SDL_Rect obstacles[], SDL_Rect people[], int nbPeople);

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
                               512,
                               128,
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
            if(people[j].x + PEOPLE_WIDTH < WINDOW_WIDTH)
                people[j].x++;
            
        }
        print(renderer, obstacles, people, nbPeople);
        SDL_Delay(100);
        
    }
    SDL_Delay(5000); /* Attendre cinq secondes, que l'utilisateur voie la fenêtre */
    
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
