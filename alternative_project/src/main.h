/*
	main.h
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 */
#include "positions.h"
#include <semaphore.h>

#ifndef MAIN
#define MAIN

#define DEFAULT_NBPEOPLE 16
#define DEFAULT_THREAD 0
#define DEFAULT_MESURE 0
#define DEFAULT_VERSION 2


typedef struct Person Person;
struct Person
{
    int x;
    int y;
    int isArrived;
};
typedef struct Point Point;
struct Point
{
    int x;
    int y;
};

typedef struct CPU_time CPU_time;
struct CPU_time
{
    double user_time;
    double system_time;
};

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople, int* option_thread, int* option_mesure, int* option_version);
CPU_time giveTimeSingleThread();

#endif
