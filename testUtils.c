/*
	testUtils.c
	Projet concurrence SI4
	Auteurs : Lafon, Monzein

	Tests des fonctions et procédures de calculs non graphique.
*/

#include <stdio.h>
#include "utils.h"

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
}
