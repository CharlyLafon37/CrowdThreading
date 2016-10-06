/*
	thread.h
*/

#ifndef THREAD
#define THREAD

#include "main.h"

void spawnPeopleThread(Person people[], int nbPeople);
void *thread_person(thread_person_data *arg);

#endif
