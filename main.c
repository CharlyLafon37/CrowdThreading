#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    
    SDL_Window* pWindow = NULL;
    SDL_Surface * window_surface = NULL;
    SDL_Surface * image_surface = NULL;
    
    pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   640,
                                   480,
                                   SDL_WINDOW_SHOWN);
    
    window_surface = SDL_GetWindowSurface(pWindow);
    
    image_surface = SDL_LoadBMP("image.bmp");
    
    SDL_BlitSurface(image_surface, NULL, window_surface, NULL);
    
    SDL_UpdateWindowSurface(pWindow);
        
    if( pWindow )
    {
        SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */
            
        SDL_DestroyWindow(pWindow);
    }
    else
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
    }
    
    SDL_FreeSurface(image_surface);
    SDL_Quit();
    
    return 0;
}
