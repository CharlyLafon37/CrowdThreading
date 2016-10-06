/*
	main.h
*/

#ifndef MAIN
#define MAIN

#include <SDL2/SDL.h>

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
    int nbPeople;
    Person* people;
};

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople);
void print(SDL_Renderer* renderer, SDL_Rect obstacles[], Person people[], int nbPeople);
void spawnPeopleThread(Person people[], int nbPeople);
void *thread_person(thread_person_data *arg);

#endif
