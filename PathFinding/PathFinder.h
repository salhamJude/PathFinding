#pragma once
#include "Init.h"
#include "Cell.h"
#include "enumeration.h"
class PathFinder
{

public :
	PathFinder(Init* init);
	~PathFinder();
	static bool findPath(GridElement** grid, int sposX, int sposY, int gposX, int gposY);
private:
	Init* init;
	Cell** cells;
};

