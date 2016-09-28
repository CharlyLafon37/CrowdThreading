#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    /**** Initialisation of SDL structures ****/
    
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    window = SDL_CreateWindow("CrowdThreading",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640,
                               480,
                               SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if(!window)
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        return -1;
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    
    /****/
    
    SDL_Rect rect;
    rect.x = 50; rect.y = 50; rect.w = 50; rect.h = 50;
    
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    
    SDL_RenderClear( renderer );
    
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    
    SDL_RenderDrawRect(renderer, &rect);
    
    SDL_RenderPresent(renderer);
    
    SDL_Delay(10000); /* Attendre dix secondes, que l'utilisateur voie la fenêtre */
            
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    
    return 0;
}
