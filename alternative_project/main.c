/*
	main.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "main.h"
#include "positions.h"
#include "utils.h"
#include "thread.h"

int main(int argc, char** argv)
{
    /**** Arguments ****/
    int nbPeople = DEFAULT_NBPEOPLE;
    int option_thread = DEFAULT_THREAD;
    int option_mesure = DEFAULT_MESURE;
    
    CPU_time debut, fin;
    
    if(argc != 1)
        argumentsTreatment(argv, argc-1, &nbPeople, &option_thread, &option_mesure);
    
    /**** Initialisation des positions des entités ****/
    Person people[nbPeople];
    
	int restant = nbPeople;

    if(option_thread == 0) // Si on simule sur 1 seul thread.
    {
        debut = giveTimeSingleThread();
        
	    spawnPeople(people, nbPeople);
        
        if(option_mesure == 0)
            printf("Personnes non sorties : %d\n", restant);
        
        int i;
	    while(restant > 0)
	    {
            for(i = 0; i < nbPeople; i++)
            {
                Point newPosition = move_people(i, people, nbPeople, XAZIMUTH, YAZIMUTH);
		    
                people[i].x = newPosition.x;
                people[i].y = newPosition.y;
                
                if(people[i].x == XAZIMUTH && people[i].y == YAZIMUTH && people[i].isArrived == 0)
                {
                    people[i].isArrived = 1;
					restant--;
                    if(option_mesure == 0)
                        printf("Personnes non sorties : %d\n", restant);
				}
            }
	    }
        
        fin = giveTimeSingleThread();
        if(option_mesure == 1)
        {
            printf("Temps CPU système consommé : %f\n", fin.system_time - debut.system_time);
            printf("Temps CPU utilisateur consommé : %f\n", fin.user_time - debut.user_time);
        }
    }
    else if(option_thread == 1) // Si on simule en divisant le terrain en 4 thread.
    {
        spawnPeopleThreadSpace(people, nbPeople, &restant); // Création des personnes et de leur thread.
        
        int i;
        while(i<300 && restant>0)
        {
            i++;
        }
    }
    else if(option_thread == 2) // Si on simule avec un thread par personne.
    {
		spawnPeopleThread(people, nbPeople, &restant); // Création des personnes et de leur thread.

		int i;
		while(i < 1000 && restant > 0)
        {
            i++;
		}
    }
    
    return 0;
}

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople, int* option_thread, int* option_mesure)
{
    int i;
    for(i = 1; i <= nbArguments; i++) // Commence à 1 car premier argument = nom executable
    {
        if(argv[i][0] == '-')
        {
            if(argv[i][1] == 'p')
            {
                char temp[2];
                temp[0] = argv[i][2];
                *nbPeople = pow(2, atoi(temp));
            }
            else if(argv[i][1] == 't')
            {
                if(argv[i][2] == '0') *option_thread=0;
                else if(argv[i][2] == '1') *option_thread=1;
                else if(argv[i][2] == '2') *option_thread=2;
            }
            else if(argv[i][1] == 'm')
            {
                *option_mesure = 1;
            }
        }
    }
}

CPU_time giveTimeSingleThread()
{
    struct rusage rusage;
    struct timeval systemTime, userTime;
    struct CPU_time cpu_time;
    
    getrusage(RUSAGE_SELF, &rusage);
    
    systemTime = rusage.ru_stime;
    userTime = rusage.ru_utime;
    
    cpu_time.system_time = (double)systemTime.tv_sec + (double)systemTime.tv_usec / 1000000.0;
    cpu_time.user_time = (double)userTime.tv_sec + (double)userTime.tv_usec / 1000000.0;
    
    return cpu_time;
}

CPU_time giveTimeMultiThread()
{
    struct rusage rusage;
    struct timeval systemTime, userTime;
    struct CPU_time cpu_time;
    
    getrusage(RUSAGE_CHILDREN, &rusage);
    
    systemTime = rusage.ru_stime;
    userTime = rusage.ru_utime;
    
    cpu_time.system_time = (double)systemTime.tv_sec + (double)systemTime.tv_usec / 1000000.0;
    cpu_time.user_time = (double)userTime.tv_sec + (double)userTime.tv_usec / 1000000.0;
    
    return cpu_time;
}
