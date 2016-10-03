/*
	positions.h
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Fonctions et procédures de calculs non graphique.
*/


#ifndef POSITIONS
#define POSITIONS

#include <SDL2/SDL.h>
#include <stdio.h>


void obstaclesLayout(SDL_Rect obstacles[]);
void spawnPeople(SDL_Rect people[], int nbPeople);

#endif
