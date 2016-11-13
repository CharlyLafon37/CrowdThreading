/*
	main.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include "main.h"
#include "utils.h"
#include "thread.h"

int main(int argc, char** argv)
{
    /**** Temps ****/
    clock_t tempsDebut, tempsFin;
    struct timeval t0, t1;
    double mesure2_sys = 0, mesure3_sys = 0, mesure4_sys = 0;
    double mesure2_user = 0, mesure3_user = 0, mesure4_user = 0;
    
    /****/
    int plateau[WINDOW_WIDTH][WINDOW_HEIGHT];
    
    /**** Arguments ****/
    int option_people = DEFAULT_PEOPLE;
    int option_thread = DEFAULT_THREAD;
    int option_mesure = DEFAULT_MESURE;
    int option_version = DEFAULT_VERSION;
    
    if(argc != 1)
        argumentsTreatment(argv, argc-1, &option_people, &option_thread, &option_mesure, &option_version);
    
    printf("Arguments d'execution : -t%d, -p%d, -e%d", option_thread, option_people, option_version);
    if(option_mesure)
        printf(", -m");
    printf("\n");
    
    /**** Semaphores ****/
    sem_t sem_plateau;
    sem_t* ptr = &sem_plateau;
    
    /**** Initialisation des entités ****/
    int nbPeople = pow(2, option_people);
    Person people[nbPeople];
    int restant = nbPeople;
    
    int nbIterations = 0;

    do
    {
        tempsDebut = clock();
        gettimeofday(&t0, NULL);
        
        if(option_version == 2 && option_thread != 0)
            sem_init(ptr, 0, 1);
        else
            ptr = NULL; // On ne veut pas de sémaphores
        
        init_plateau(plateau);
        
        if(option_thread == 0) // Si on simule sur 1 seul thread.
        {
            spawnPeople(people, nbPeople, plateau);
            
            if(option_mesure == 0)
                printf("Personnes non sorties : %d\n", restant);
            
            int i;
            while(restant > 0)
            {
                for(i = 0; i < nbPeople; i++)
                {
                    Point newPosition = move_people(i, people, nbPeople, XAZIMUTH, YAZIMUTH, plateau, ptr);
                    
                    if(people[i].x == XAZIMUTH && people[i].y == YAZIMUTH && people[i].isArrived == 0)
                    {
                        people[i].isArrived = 1;
                        restant--;
                        if(option_mesure == 0)
                            printf("Personnes non sorties : %d\n", restant);
                    }
                }
            }
        }
        else if(option_thread == 1) // Si on simule en divisant le terrain en 4 thread.
        {
            spawnPeopleThreadSpace(people, nbPeople, &restant, option_mesure, plateau, ptr); // Création des personnes et de leur thread.
        }
        else if(option_thread == 2) // Si on simule avec un thread par personne.
        {
            spawnPeopleThread(people, nbPeople, &restant, option_mesure, plateau, ptr); // Création des personnes et de leur thread.
        }
        
        tempsFin = clock();
        gettimeofday(&t1, NULL);
        
        if(option_mesure == 1)
        {
            switch(nbIterations+1)
            {
                case 2 : {
                    mesure2_sys = (double)(tempsFin - tempsDebut) / CLOCKS_PER_SEC;
                    mesure2_user = ((double)((t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec) - t0.tv_usec)/1000000;
                    break;
                }
                case 3 : {
                    mesure3_sys = (double)(tempsFin - tempsDebut) / CLOCKS_PER_SEC;
                    mesure3_user = ((double)((t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec) - t0.tv_usec)/1000000;
                    break;
                }
                case 4 : {
                    mesure4_sys = (double)(tempsFin - tempsDebut) / CLOCKS_PER_SEC;
                    mesure4_user = ((double)((t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec) - t0.tv_usec)/1000000;
                    break;
                }
                default : break;
            }
        }
        restant = nbPeople;
        nbIterations++;
        
        if(option_mesure)
            printf("Iteration %d finie\n", nbIterations);
    }
    while(option_mesure == 1 && nbIterations < 5);
    
    if(option_mesure == 1)
    {
        printf("Moyenne des 3 mesures intermediaires parmi les 5 mesures :\n");
        printf("Temps CPU systeme consomme : %.6fs\n", (mesure2_sys + mesure3_sys + mesure4_sys) / 3);
        printf("Temps utilisateur consomme : %.6fs\n", (mesure2_user + mesure3_user + mesure4_user) / 3);
    }
    
    if(option_version == 2 && option_thread != 0)
        sem_destroy(ptr);
    
    return 0;
}

void argumentsTreatment(char** argv, int nbArguments, int* option_people, int* option_thread, int* option_mesure, int* option_version)
{
    int i;
    for(i = 1; i <= nbArguments; i++) // Commence à 1 car premier argument = nom executable
    {
        if(argv[i][0] == '-')
        {
            char temp[2];
            temp[0] = argv[i][2];
            
            if(argv[i][1] == 'p')
                *option_people = atoi(temp);
            else if(argv[i][1] == 't')
                *option_thread = atoi(temp);
            else if(argv[i][1] == 'm')
                *option_mesure = 1;
            else if(argv[i][1] == 'e')
                *option_version = atoi(temp);
        }
    }
}
