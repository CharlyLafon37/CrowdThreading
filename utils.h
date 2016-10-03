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

#define OBSTACLE_WIDTH 16
#define OBSTACLE_LEFT_HEIGHT 60
#define OBSTACLE_RIGHT_HEIGHT 56
#define XOBSTACLE_LEFT_TOP 0
#define YOBSTACLE_LEFT_TOP 0
#define XOBSTACLE_LEFT_BOTTOM 0
#define YOBSTACLE_LEFT_BOTTOM WINDOW_HEIGHT-OBSTACLE_LEFT_HEIGHT
#define XOBSTACLE_RIGHT_TOP 128-OBSTACLE_WIDTH
#define YOBSTACLE_RIGHT_TOP 0
#define XOBSTACLE_RIGHT_BOTTOM 128-OBSTACLE_WIDTH
#define YOBSTACLE_RIGHT_BOTTOM  WINDOW_HEIGHT-OBSTACLE_RIGHT_HEIGHT

int move_to_azimuth(int positionX, int positionY, int azimuthX, int azimuthY);

SDL_Point move_people(int indexPeople, SDL_Rect* peoples, int nbPeople, int azimuthX, int azimuthY);
