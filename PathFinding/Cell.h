#pragma once
#include <iostream>
class Cell
{
public:
	Cell();
	Cell(float h, float g, int x, int y);
	Cell(int x, int y);
	void setPosition(int x, int y);
	void clear();
	void display() const;
	bool hasCost() const ;
private:
	int posx;
	int posY;
	float h;
	float g;
	float f;
	bool gotCost;
};


