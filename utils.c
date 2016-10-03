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
	Renvoie un point pour le deplacement de la personne en paramètre.
*/
SDL_Point move_people(int indexPeople, SDL_Rect* peoples, int nbPeople, int azimuthX, int azimuthY){
	SDL_Point result = {0,0};

	SDL_Point people = {peoples[indexPeople].x,peoples[indexPeople].y};

	int direction = move_to_azimuth(people.x,people.y,azimuthX,azimuthY);


	return result;
}




