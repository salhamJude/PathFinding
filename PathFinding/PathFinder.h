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

struct Path {
	struct Path* parent = NULL;
	int x = -1, y = -1;
};


class PathFinder
{

public :
	PathFinder(Init* init);
	~PathFinder();
	bool findPath(GridElement** grid, int sposX, int sposY, int gposX, int gposY);
private:
	
	void showPaths();
	float cost;
	float lambda;
	Init* init;
	Cell** cells;
	float D;
	float D2;
	unsigned int roads;
	unsigned int visited;
	struct Path* paths;
};

