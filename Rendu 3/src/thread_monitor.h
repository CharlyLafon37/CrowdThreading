/*
	thread_monitor.h
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 */


#ifndef THREAD_MONITOR
#define THREAD_MONITOR

#include "main.h"

#define NB_THREAD 4

typedef struct monitor_thread_person_data monitor_thread_person_data;
struct monitor_thread_person_data
{
    int n;
    int nbPeople;
    Person* people;
    pthread_mutex_t* mutex;
    pthread_cond_t* var_cond;
    int* acces;
    int (*plateau)[WINDOW_WIDTH][WINDOW_HEIGHT];
};

typedef struct monitor_thread_space_data monitor_thread_space_data;
struct monitor_thread_space_data
{
    int n;
    int *restant;
    int nbPeople;
    Person* people;
    int nbPeopleSpace;
    int* peopleSpace;
    monitor_thread_space_data* datas;
    int option_mesure;

    pthread_mutex_t mutex;
    pthread_cond_t var_cond;
    int acces;

    sem_t* sem_join;
    int (*plateau)[WINDOW_WIDTH][WINDOW_HEIGHT];
};

void monitor_spawnPeopleThread(Person people[], int nbPeople, int *restant, int option_mesure, int plateau[][WINDOW_HEIGHT]);
void *monitor_thread_person(monitor_thread_person_data *arg);
void monitor_spawnPeopleThreadSpace(Person people[], int nbPeople, int *restant, int option_mesure, int plateau[][WINDOW_HEIGHT]);
void *monitor_thread_space(monitor_thread_space_data *arg);


#endif
