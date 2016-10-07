/*
	main.h
*/

#ifndef MAIN
#define MAIN

#define DEFAULT_NBPEOPLE 16
#define DEFAULT_THREAD 0
#define DEFAULT_MESURE 0

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

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople, int* option_thread, int* option_mesure);

#endif
