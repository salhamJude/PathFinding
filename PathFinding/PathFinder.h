#pragma once
#include "Init.h"
#include "Cell.h"
#include "enumeration.h"
#include <ctime>
#include <stdlib.h>
#include <cmath>

#ifdef _WIN32
	#include<Windows.h>
#elif __linux__
	#include<unistd.h>
#elif __APPLE__
	#include<unistd.h>
#elif __unix__
	#include<unistd.h>
#endif
class PathFinder
{

public :
	PathFinder(Init* init);
	~PathFinder();
	bool findPath(GridElement** grid, int sposX, int sposY, int gposX, int gposY);
private:
	Init* init;
	Cell** cells;
	float cost;
	float lambda;
	float D;
	float D2;
	Direction winner(float* scores, int pos[8][2], int gposX, int gposY);
};

