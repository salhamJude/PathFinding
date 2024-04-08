#pragma once

#include <iostream>
#include "enumeration.h"
#include <ctime>
#include <stdlib.h>
#include "Cell.h"

#define OS_WINDOWS 1
#define OS_LINUX   2
#define OS_MACOS   3
#define OS_UNIX    4
#define OS_UNKNOWN 0



class Init
{

public :
	Init();
	~Init();
	void drawGrid();
	void drawGrid(float* scores,Cell current, Cell start, Cell goal);
	bool isWall(int x, int y);
	bool isRoad(int x, int y);
	bool isPath(int x, int y);
	bool isGoalPosition(int x, int y);
	bool isStartPositon(int x, int y);
	int* getStartPosition();
	int* getGoalPosition();
	int getGridsize();
	GridElement**  getGrid();
private :
	int gridsize;
	int start_position[2];
	int goal_postion [2];
	GridElement** grid;
	int os; 
	void generateWalls();
	void generateWall(int posX, int posY, Direction dir, int length);
	void initGrid();
	void setStartPostion(int x, int y);
	void setGoalPosition(int x, int y);
};

