/*
	utils.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/

#include <stdio.h>
#include <SDL2/SDL.h>
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
	else if(positionX<azimuthY){
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
int can_move(int indexPeople, SDL_Rect* peoples, int nbPeople, SDL_Point moveTo){

	// Bordure de la fenêtre
	if(moveTo.x<0 || moveTo.x+PEOPLE_WIDTH>=WINDOW_WIDTH)
		return 0;
	if(moveTo.y<0 || moveTo.y+PEOPLE_HEIGHT>=WINDOW_HEIGHT)
		return 0;
	// Obstacles
	// Obstacle haut gauche
	if(moveTo.x<XOBSTACLE_LEFT_TOP+OBSTACLE_WIDTH && moveTo.x+PEOPLE_WIDTH>=XOBSTACLE_LEFT_TOP)
		return 0;
	if(moveTo.y<YOBSTACLE_LEFT_TOP+OBSTACLE_LEFT_HEIGHT && moveTo.y+PEOPLE_HEIGHT>=YOBSTACLE_LEFT_TOP)
		return 0;
	// Obstacle bas gauche
	if(moveTo.x<XOBSTACLE_LEFT_BOTTOM+OBSTACLE_WIDTH && moveTo.x+PEOPLE_WIDTH>=XOBSTACLE_LEFT_BOTTOM)
		return 0;
	if(moveTo.y<YOBSTACLE_LEFT_BOTTOM+OBSTACLE_LEFT_HEIGHT && moveTo.y+PEOPLE_HEIGHT>=YOBSTACLE_LEFT_BOTTOM)
		return 0;
	// Obstacle haut gauche
	if(moveTo.x<XOBSTACLE_RIGHT_TOP+OBSTACLE_WIDTH && moveTo.x+PEOPLE_WIDTH>=XOBSTACLE_RIGHT_TOP)
		return 0;
	if(moveTo.y<YOBSTACLE_RIGHT_TOP+OBSTACLE_RIGHT_HEIGHT && moveTo.y+PEOPLE_HEIGHT>=YOBSTACLE_RIGHT_TOP)
		return 0;
	// Obstacle bas gauche
	if(moveTo.x<XOBSTACLE_RIGHT_BOTTOM+OBSTACLE_WIDTH && moveTo.x+PEOPLE_WIDTH>=XOBSTACLE_RIGHT_BOTTOM)
		return 0;
	if(moveTo.y<YOBSTACLE_RIGHT_BOTTOM+OBSTACLE_RIGHT_HEIGHT && moveTo.y+PEOPLE_HEIGHT>=YOBSTACLE_RIGHT_BOTTOM)
		return 0;

	// Personnes
	int i=0;
	for(i=0;i<nbPeople;i++){
		if(i!=indexPeople){
			if(moveTo.x<peoples[i].x+PEOPLE_WIDTH && moveTo.x+PEOPLE_WIDTH>=peoples[i].x)
				return 0;
			if(moveTo.y<peoples[i].y+PEOPLE_HEIGHT && moveTo.y+PEOPLE_HEIGHT>=peoples[i].y)
				return 0;
		}
	}

	return 1;
}

/*
	Renvoie un point pour le deplacement de la personne en paramètre.
*/
SDL_Point move_people(int indexPeople, SDL_Rect* peoples, int nbPeople, int azimuthX, int azimuthY){

	SDL_Point people = {peoples[indexPeople].x,peoples[indexPeople].y};
	SDL_Point move_to = {people.x,people.y};

	int direction = move_to_azimuth(people.x,people.y,azimuthX,azimuthY);
	
	switch(direction){
		case STAY:{
			return people;
		}// 4 points cardinaux
		case NORTH:{
			move_to.y=people.y-1;
			if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
				return move_to;
			else
				return people;
		}
		case SOUTH:{
			move_to.y=people.y+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
				return move_to;
			else
				return people;
		}
		case EAST:{
			move_to.y=people.x+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
				return move_to;
			else
				return people;
		}
		case WEST:{
			move_to.y=people.x-1;
			if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
				return move_to;
			else
				return people;
		}//4 diagonales
		case NORTHEAST:{
			move_to.y=people.y-1;
			move_to.x=people.x+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
				return move_to;
			else{
				move_to.x=people.x;
				if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
					return move_to;
				else{
					move_to.y=people.y;
					move_to.x=people.x+1;
					if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
						return move_to;
					else
						return people;
				}
			}
		}
		case SOUTHEAST:{
			move_to.y=people.y+1;
			move_to.x=people.x+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
				return move_to;
			else{
				move_to.x=people.x;
				if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
					return move_to;
				else{
					move_to.y=people.y;
					move_to.x=people.x+1;
					if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
						return move_to;
					else
						return people;
				}
			}
		}
		case NORTHWEST:{
			move_to.y=people.y-1;
			move_to.x=people.x-1;
			if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
				return move_to;
			else{
				move_to.x=people.x;
				if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
					return move_to;
				else{
					move_to.y=people.y;
					move_to.x=people.x-1;
					if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
						return move_to;
					else
						return people;
				}
			}
		}
		case SOUTHWEST:{
			move_to.y=people.y+1;
			move_to.x=people.x+1;
			if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
				return move_to;
			else{
				move_to.x=people.x;
				if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
					return move_to;
				else{
					move_to.y=people.y;
					move_to.x=people.x+1;
					if(can_move(indexPeople, peoples, nbPeople, move_to)==1)
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




