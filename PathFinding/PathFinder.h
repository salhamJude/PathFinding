#pragma once
#include "Init.h"
#include "Cell.h"
#include "enumeration.h"
#include <ctime>
#include <stdlib.h>

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
	Direction winner(float* scores, int pos[4][4], int gposX, int gposY);
};

