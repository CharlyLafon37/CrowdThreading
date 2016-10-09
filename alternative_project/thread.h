/*
	thread.h
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 */


#ifndef THREAD
#define THREAD

#include "main.h"

#define NB_THREAD 4

typedef struct thread_person_data thread_person_data;
struct thread_person_data
{
    int n;
    int nbPeople;
    Person* people;
};

typedef struct thread_space_data thread_space_data;
struct thread_space_data
{
    int n;
    int *restant;
    int nbPeople;
    Person* people;
    int nbPeopleSpace;
    int* peopleSpace;
	thread_space_data* datas;
    int option_mesure;
};

void spawnPeopleThread(Person people[], int nbPeople, int *restant, int option_mesure);
void *thread_person(thread_person_data *arg);
void spawnPeopleThreadSpace(Person people[], int nbPeople, int *restant, int option_mesure);
void *thread_space(thread_space_data *arg);


#endif
