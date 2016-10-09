/*
	utils.h
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 */


#ifndef UTILS
#define UTILS

#include "main.h"
#include "positions.h"

#define ERROR -1
#define STAY 0
#define NORTH 1
#define NORTHEAST 2
#define EAST 3
#define SOUTHEAST 4
#define SOUTH 5
#define SOUTHWEST 6
#define WEST 7
#define NORTHWEST 8

#define XTHREAD_FIRST 0
#define XTHREAD_SECOND WINDOW_WIDTH/4
#define XTHREAD_THIRD WINDOW_WIDTH/2
#define XTHREAD_FOURTH 3*WINDOW_WIDTH/4

int move_to_azimuth(int positionX, int positionY, int azimuthX, int azimuthY);
Point move_people(int indexPeople, Person peoples[], int nbPeople, int azimuthX, int azimuthY);
int indice_thread(int x, int y);
void move_index_people(int* nb_people_1, int* nb_people_2, int tab1[], int tab2[], int index);

#endif
