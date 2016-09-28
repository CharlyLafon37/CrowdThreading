/*
	utils.h
*/

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
#define WIDTH 512
#define HEIGHT 128

int move_to_azimuth(int positionX, int positionY, int azimuthX, int azimuthY);
