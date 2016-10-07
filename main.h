/*
	main.h
*/

#ifndef MAIN
#define MAIN

#include <SDL2/SDL.h>

#define DEFAULT_NBPEOPLE 16
#define DEFAULT_THREAD 0
#define DEFAULT_MESURE 0

typedef struct Person Person;
struct Person
{
    SDL_Rect position;
    int isArrived;
};

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople, int* option_thread, int* option_mesure);
void print(SDL_Renderer* renderer, SDL_Rect obstacles[], Person people[], int nbPeople);

#endif
