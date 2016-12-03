/*
	utils_monitor.h
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 */

#ifndef UTILS_MONITOR
#define UTILS_MONITOR

#include "utils.h"

Point monitor_move_people(int indexPeople, Person peoples[], int nbPeople, int azimuthX, int azimuthY, int plateau[][WINDOW_HEIGHT]);
Point monitor_move_people_space(int indexPeople, Person peoples[], int nbPeople, int azimuthX, int azimuthY, int plateau[][WINDOW_HEIGHT],int indice);

#endif
