#pragma once
#include <iostream>
#include <math.h>
#include "enumeration.h"
class Cell
{
public:
	Cell();
	Cell(float h, float g, int x, int y, GridElement type);
	Cell(int x, int y, GridElement type);
	void setPosition(int x, int y);
	int getXposition() const;
	int getYposition() const;
	void clear();
	void display() const;
	bool hasCost() const ;
	float calculateScore(float cost, float lambda, int gposX, int gposY, float parentg, float d, float d2);
	float getG() const;
	Cell* operator=(const Cell& cell);
	bool isSame(const Cell& cell) const;
	GridElement getType() const;
	void setType(GridElement ttype);
private:
	int posx;
	int posY;
	float h;
	float g;
	float f;
	bool gotScore;
	GridElement type;

};


