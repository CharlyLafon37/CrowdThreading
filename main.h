/*
	main.h
*/

#ifndef MAIN
#define MAIN

#include <SDL2/SDL.h>

#define DEFAULT_NBPEOPLE 16
#define DEFAULT_THREAD 0

typedef struct Person Person;
struct Person
{
    SDL_Rect person;
    int isArrived;
};
typedef struct thread_person_data thread_person_data;
struct thread_person_data
{
    int n;
    int *restant;
    int nbPeople;
    Person* people;
};

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople, int* option_thread);
void print(SDL_Renderer* renderer, SDL_Rect obstacles[], Person people[], int nbPeople);
int everyOneIsArrived(Person people[], int nbPeople); // 0 if some people are not arrived, 1 if everybody is arrived

#endif
