#include "Cell.h"

Cell::Cell():h(0), g(0), posx(0), posY(0), f(0.0), gotCost(false)
{
}

Cell::Cell(float h, float g, int x, int y) : h(h), g(g), posx(x), posY(y), f(0.0), gotCost(false)
{
}

Cell::Cell(int x, int y) : h(0), g(0), posx(x), posY(y), f(0.0), gotCost(false)
{
}

void Cell::setPosition(int x, int y)
{
	posx = x;
	posY = y;
}

void Cell::clear()
{
	h = 0.0;
	g = 0.0;
	f = 0.0;
	gotCost = false;
}

void Cell::display() const
{
	std::cout << posx << "," << posY << std::endl;
}

bool Cell::hasCost() const 
{
	return gotCost;
}
