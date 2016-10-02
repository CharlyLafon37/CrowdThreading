#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 128

void obstaclesLayout(SDL_Rect obstacles[]);

int main(int argc, char** argv)
{
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
    
    /****/
    
    SDL_SetRenderDrawColor(renderer, 175, 175, 175, 255); // Background = grey
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Rectangles = black
    
    SDL_Rect obstacles[4];
    
    obstaclesLayout(obstacles);
    
    // Render rect
    SDL_RenderFillRects(renderer, obstacles, 4);
    
    // Render the rect to the screen
    SDL_RenderPresent(renderer);
    
    SDL_Delay(5000); /* Attendre cinq secondes, que l'utilisateur voie la fenêtre */
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    
    return 0;
}

void obstaclesLayout(SDL_Rect obstacles[])
{
    obstacles[0].w = 16; obstacles[0].h = 60; obstacles[0].x = 0; obstacles[0].y = 0;
    obstacles[1].w = 16; obstacles[1].h = 60; obstacles[1].x = 0; obstacles[1].y = WINDOW_HEIGHT - obstacles[1].h;
    obstacles[2].w = 16; obstacles[2].h = 56; obstacles[2].x = 128 - obstacles[2].w; obstacles[2].y = 0;
    obstacles[3].w = 16; obstacles[3].h = 56; obstacles[3].x = 128 - obstacles[3].w; obstacles[3].y = WINDOW_HEIGHT - obstacles[3].h;
}
