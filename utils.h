/*
	utils.h
*/
#include <SDL2/SDL.h>

#define ERROR -1
#define STAY 0
#define NORTH 1
#define NORTHEAST 2
#define EAST 3
#define SOUTHEAST 4
#define SOUTH 5
#define SOUTHWEST 6
#define WEST 7
#define NORTHWEST 8

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 128
#define DEFAULT_NBPEOPLE 16
#define PEOPLE_WIDTH 4
#define PEOPLE_HEIGHT 4

int move_to_azimuth(int positionX, int positionY, int azimuthX, int azimuthY);

SDL_Point move_people(int indexPeople, SDL_Rect* peoples, int nbPeople);
