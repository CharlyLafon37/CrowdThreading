/*
	testUtils.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Tests des fonctions et procédures de calculs non graphique.
*/

#include <stdio.h>
#include "utils.h"
#include "positions.h"

int main(){

	printf("--- Test move_to_azimuth\t---");
	int azimuthX=50,azimuthY=50;
	int positionX,positionY;

	printf("Azimuth (%d,%d)\n",azimuthX,azimuthY);
	positionX=50;positionY=60;
	printf("Position (%d,%d) le déplacement est bien NORTH = %d\n"
		,positionX,positionY,(NORTH==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));
	positionX=50;positionY=40;
	printf("Position (%d,%d) le déplacement est bien SOUTH = %d\n"
		,positionX,positionY,(SOUTH==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));

	positionX=60;positionY=60;
	printf("Position (%d,%d) le déplacement est bien NORTHWEST = %d\n"
		,positionX,positionY,(NORTHWEST==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));
	positionX=60;positionY=40;
	printf("Position (%d,%d) le déplacement est bien SOUTHWEST = %d\n"
		,positionX,positionY,(SOUTHWEST==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));

	positionX=40;positionY=60;
	printf("Position (%d,%d) le déplacement est bien NORTHEAST = %d\n"
		,positionX,positionY,(NORTHEAST==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));
	positionX=40;positionY=40;
	printf("Position (%d,%d) le déplacement est bien SOUTHEAST = %d\n"
		,positionX,positionY,(SOUTHEAST==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));

	positionX=40;positionY=50;
	printf("Position (%d,%d) le déplacement est bien EAST = %d\n"
		,positionX,positionY,(EAST==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));
	positionX=60;positionY=50;
	printf("Position (%d,%d) le déplacement est bien WEST = %d\n"
		,positionX,positionY,(WEST==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));

	positionX=50;positionY=50;
	printf("Position (%d,%d) le déplacement est bien STAY = %d\n"
		,positionX,positionY,(STAY==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));
	positionX=-1;positionY=50;
	printf("Position (%d,%d) le déplacement est bien ERROR = %d\n"
		,positionX,positionY,(ERROR==move_to_azimuth(positionX,positionY,azimuthX,azimuthY)));

	printf("--- Test can_move\t---");
	
	SDL_Rect people[16];
	spawnPeople(people, 16);
	people[0].x=100;
	people[0].y=64;
	SDL_Point result = move_people(0, people, 16, 0, 64);
	printf("Position avant(%d,%d)\t Position apres(%d,%d)\n",people[0].x,people[0].y,result.x,result.y);













}
