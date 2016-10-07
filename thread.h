/*
	thread.h
*/

#ifndef THREAD
#define THREAD

#include "main.h"

typedef struct thread_person_data thread_person_data;
struct thread_person_data
{
    int n;
    int *restant;
    int nbPeople;
    Person* people;
};

void spawnPeopleThread(Person people[], int nbPeople, int *restant);
void *thread_person(thread_person_data *arg);

#endif
