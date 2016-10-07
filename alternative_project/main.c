#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "main.h"
#include "positions.h"
#include "utils.h"
#include "thread.h"

int main(int argc, char** argv)
{
    /**** Arguments handling ****/
    int nbPeople = DEFAULT_NBPEOPLE;
    int option_thread = DEFAULT_THREAD;
    int option_mesure = DEFAULT_MESURE;
    
    if(argc != 1)
        argumentsTreatment(argv, argc-1, &nbPeople, &option_thread, &option_mesure);
    
    /**** Initialisation of entities' position ****/
    Person people[nbPeople];
    
	int restant = nbPeople;

    if(option_thread == 0) // Si on simule sur 1 seul thread.
    {
	    spawnPeople(people, nbPeople);
        
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
				}
            }
            printf("%d\n", restant);
            usleep(30000);
	    }
    }
    else if(option_thread == 1) // Si on simule en divisant le terrain en 4 thread.
    {
		
    }
    else if(option_thread == 2) // Si on simule avec un thread par personne.
    {
		spawnPeopleThread(people, nbPeople, &restant); // Création des personnes et de leur thread.

		int i;
		while(i<300 && restant>0)
        {
            i++;
            usleep(50000);
		}
    }
    
    return 0;
}

void argumentsTreatment(char** argv, int nbArguments, int* nbPeople, int* option_thread, int* option_mesure)
{
    int i;
    for(i = 1; i <= nbArguments; i++) // Begins to 1 because first argument = name of executable
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
