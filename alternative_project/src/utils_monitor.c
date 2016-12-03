/*
	utils_monitor.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/

#include <stdio.h>
#include "utils_monitor.h"

/*
	Déplace la personne et renvoie sa position.
*/
Point monitor_move_people(int indexPeople, Person peoples[], int nbPeople, int azimuthX, int azimuthY, int plateau[][WINDOW_HEIGHT]){
	
    int i ,j;
    
    Person p = peoples[indexPeople];
    int oldx = p.x, oldy = p.y;
    
	Point pt = point_move_people(indexPeople, peoples, nbPeople, azimuthX, azimuthY, plateau);
    
	//Si on se déplace
    if(!(pt.x==oldx && pt.y==oldy))
    {
        // On récupère la nouvelle position
	    peoples[indexPeople].x=pt.x;
	    peoples[indexPeople].y=pt.y;
        
        // On passe à 0 l'ancienne position
	    for(i=p.x;i<p.x+PEOPLE_WIDTH;i++){
		    for(j=p.y;j<p.y+PEOPLE_HEIGHT;j++){
			    plateau[i][j] = 0;
		    }
	    }
        // On passe à 1 la nouvelle position si la personne n'est pas arrivé
        if(pt.x!=XAZIMUTH || pt.y!=YAZIMUTH){
	        for(i=pt.x;i<pt.x+PEOPLE_WIDTH;i++){
		        for(j=pt.y;j<pt.y+PEOPLE_HEIGHT;j++){
			        plateau[i][j] = 1;
		        }
	        }
        }
    }
    
	return pt;
}

/*
	Déplace la personne et renvoie sa position pour l'algo des 4 threads
*/
Point monitor_move_people_space(int indexPeople, Person peoples[], int nbPeople, int azimuthX, int azimuthY, int plateau[][WINDOW_HEIGHT], int indice){
	
    int i ,j;
    
    Person p = peoples[indexPeople];
    int oldx = p.x, oldy = p.y;
    int newIndice;
    
	Point pt = point_move_people(indexPeople, peoples, nbPeople, azimuthX, azimuthY, plateau);
    
	//Si on se déplace
    if(!(pt.x==oldx && pt.y==oldy))
    {
        // On récupère la nouvelle position
	    peoples[indexPeople].x=pt.x;
	    peoples[indexPeople].y=pt.y;
        
        newIndice = indice_thread(pt.x, pt.y);

        // On passe à 0 l'ancienne position
	    for(i=p.x;i<p.x+PEOPLE_WIDTH;i++){
		    for(j=p.y;j<p.y+PEOPLE_HEIGHT;j++){
			    plateau[i][j] = 0;
		    }
	    }
        // On passe à 1 la nouvelle position si la personne n'est pas arrivé
        if(pt.x!=XAZIMUTH || pt.y!=YAZIMUTH){
	        for(i=pt.x;i<pt.x+PEOPLE_WIDTH;i++){
		        for(j=pt.y;j<pt.y+PEOPLE_HEIGHT;j++){
			        plateau[i][j] = 1;
		        }
	        }
        }
    }

    return pt;
}

