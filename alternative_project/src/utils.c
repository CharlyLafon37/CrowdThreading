/*
	utils.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/

#include <stdio.h>
#include "utils.h"

/*
	Renvoie un entier selon la direction à suivre.
	return : NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST, STAY, ERROR.
*/
int move_to_azimuth(int positionX, int positionY, int azimuthX, int azimuthY){
	// Verification des parametres.
	if(positionX<0 || positionX>=WINDOW_WIDTH || positionY<0 || positionY>=WINDOW_HEIGHT)
		return ERROR;
	if(azimuthX<0 || azimuthX>=WINDOW_WIDTH || azimuthY<0 || azimuthY>=WINDOW_HEIGHT)
		return ERROR;
	// Si il faut se delacer vers l'ouest.
	if(positionX>azimuthX){
		if(positionY>azimuthY)
			return NORTHWEST;
		else if(positionY<azimuthY)
			return SOUTHWEST;
		else
			return WEST;
	} 
	// Si il faut se deplacer vers l'est.
	else if(positionX<azimuthX){
		if(positionY>azimuthY)
			return NORTHEAST;
		else if(positionY<azimuthY)
			return SOUTHEAST;
		else
			return EAST;
	} 
	// Si il ne faut pas se deplacer en horizontale
	else{
		if(positionY>azimuthY)
			return NORTH;
		else if(positionY<azimuthY)
			return SOUTH;
		else
			return STAY;
	}
}

/*
	Retourne 1 si la personne peut se deplacer au point indique.
	Sinon, renvoie 0;
*/
int can_move(int indexPeople, Person* peoples, int nbPeople, Point moveTo, int plateau[][WINDOW_HEIGHT]){

	// Bordure de la fenêtre
	if(moveTo.x<0 || moveTo.x+PEOPLE_WIDTH>=WINDOW_WIDTH)
		{return 0;}
	if(moveTo.y<0 || moveTo.y+PEOPLE_HEIGHT>=WINDOW_HEIGHT)
		{return 0;}

    Person p = peoples[indexPeople];

	int i=0;

	// Personnes et obstacles
	if(p.x>moveTo.x){
		for(i=moveTo.y;i<moveTo.y+PEOPLE_HEIGHT;i++){
			if(plateau[moveTo.x][i] != 0) return 0;
		}
	}else if(p.x<moveTo.x){
		for(i=moveTo.y;i<moveTo.y+PEOPLE_HEIGHT;i++){
			if(plateau[moveTo.x+PEOPLE_WIDTH-1][i] != 0) return 0;
		}
	}
	if(p.y>moveTo.y){
		for(i=moveTo.x;i<moveTo.x+PEOPLE_WIDTH;i++){
			if(plateau[i][moveTo.y] != 0) return 0;
		}
	}else if(p.y<moveTo.y){
		for(i=moveTo.x;i<moveTo.x+PEOPLE_WIDTH;i++){
			if(plateau[i][moveTo.y+PEOPLE_HEIGHT-1] != 0) return 0;
		}
	}

	return 1;
}

/*
	Renvoie un point pour le deplacement de la personne en paramètre.
*/
Point point_move_people(int indexPeople, Person peoples[], int nbPeople, int azimuthX, int azimuthY, int plateau[][WINDOW_HEIGHT]){

	Point people = {peoples[indexPeople].x,peoples[indexPeople].y};
	Point move_to = {people.x,people.y};

	int direction = move_to_azimuth(people.x,people.y,azimuthX,azimuthY);
	switch(direction){
		case STAY:{
			return people;
		}// 4 points cardinaux
		case NORTH:{
			move_to.y=people.y-1;
			if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
				return move_to;
			else
				return people;
		}
		case SOUTH:{
			move_to.y=people.y+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
				return move_to;
			else
				return people;
		}
		case EAST:{
			move_to.x=people.x+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
				return move_to;
			else
				return people;
		}
		case WEST:{
			move_to.x=people.x-1;
			if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
				return move_to;
			else
				return people;
		}//4 diagonales
		case NORTHEAST:{
			move_to.y=people.y-1;
			move_to.x=people.x+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
				return move_to;
			else{
				move_to.x=people.x;
				if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
					return move_to;
				else{
					move_to.y=people.y;
					move_to.x=people.x+1;
					if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
						return move_to;
					else
						return people;
				}
			}
		}
		case SOUTHEAST:{
			move_to.y=people.y+1;
			move_to.x=people.x+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
				return move_to;
			else{
				move_to.x=people.x;
				if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
					return move_to;
				else{
					move_to.y=people.y;
					move_to.x=people.x+1;
					if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
						return move_to;
					else
						return people;
				}
			}
		}
		case NORTHWEST:{
			move_to.y=people.y-1;
			move_to.x=people.x-1;
			if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
				return move_to;
			else{
				move_to.x=people.x;
				if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
					return move_to;
				else{
					move_to.y=people.y;
					move_to.x=people.x-1;
					if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
						return move_to;
					else
						return people;
				}
			}
		}
		case SOUTHWEST:{
			move_to.y=people.y+1;
			move_to.x=people.x-1;
			if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
				return move_to;
			else{
				move_to.x=people.x;
				if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
					return move_to;
				else{
					move_to.y=people.y;
					move_to.x=people.x-1;
					if(can_move(indexPeople, peoples, nbPeople, move_to, plateau)==1)
						return move_to;
					else
						return people;
				}
			}
		}
		default:{
			return people;
		}
	}

	return people;
}

/*
	Retourne l'indice du thread correspondant à la position du données.
 */
int indice_thread(int x, int y){
    
    if(x<XTHREAD_SECOND)
        return 0;
    else if(x<XTHREAD_THIRD)
        return 1;
    else if(x<XTHREAD_FOURTH)
        return 2;
    else 
        return 3;
}

/*
	Déplace la personne et renvoie sa position.
*/
Point move_people(int indexPeople, Person peoples[], int nbPeople, int azimuthX, int azimuthY, int plateau[][WINDOW_HEIGHT], sem_t* sem_plateau){
	
    int i ,j;
    
    Person p = peoples[indexPeople];
    int oldx = p.x, oldy = p.y;

	if(sem_plateau != NULL)
        sem_wait(sem_plateau);
    
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
    if(sem_plateau != NULL)
        sem_post(sem_plateau);
    
	return pt;
}

/*
	Déplace la personne et renvoie sa position pour l'algo des 4 threads
*/
Point move_people_space(int indexPeople, Person peoples[], int nbPeople, int azimuthX, int azimuthY, int plateau[][WINDOW_HEIGHT], sem_t* sem_space1, sem_t* sem_space2, int indice){
	
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
        if(sem_space2 != NULL && indice!=newIndice && indice>0){
               sem_wait(sem_space2);
        }

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
	Deplacement d'un tableau à un autre de l'indice d'un personnage
 */
void move_index_people(int* nb_people_1, int* nb_people_2, int tab1[], int tab2[], int index){
    
    // Garder en mémoire l'index de la personne
    int temp=tab1[index];
    
    // Ajouter l'index de la personne sur le nouveau tableau
    tab2[(*(nb_people_2))]=temp;
    (*(nb_people_2))=(*(nb_people_2))+1;
    
    // Supprimer l'index du tableau 1
    int i=0;
    for(i=index;i<(*(nb_people_1))-1;i++){
        tab1[i]=tab1[i+1];
    }
    tab1[--(*(nb_people_1))]=-1;
}
