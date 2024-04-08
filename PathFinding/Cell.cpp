#include "Cell.h"

Cell::Cell():h(0), g(0), posx(0), posY(0), f(0.0), gotScore(false), type(ROAD)
{
}

Cell::Cell(float h, float g, int x, int y, GridElement type) : h(h), g(g), posx(x), posY(y), f(0.0), gotScore(false), type(type)
{
}

Cell::Cell(int x, int y, GridElement type) : h(0), g(0), posx(x), posY(y), f(0.0), gotScore(false), type(type)
{
}

void Cell::setPosition(int x, int y)
{
	posx = x;
	posY = y;
}

int Cell::getXposition() const
{
	return posx;
}

int Cell::getYposition() const
{
	return posY;
}

void Cell::clear()
{
	h = 0.0;
	g = 0.0;
	f = 0.0;
	gotScore = false;
}

void Cell::display() const
{
	std::cout << posx << "," << posY << std::endl;
}

bool Cell::hasCost() const 
{
	return gotScore;
}

float Cell::calculateScore(float cost, float lambda, int gposX, int gposY, float parentg, float d, float d2)
{

	if (gotScore)
		return f;
	h = cost * (d * ((abs(posx - gposX) + abs(posY - gposY)) + (d2 - (2 * d) * fmin(abs(posx - gposX), abs(posY - gposY)))));
	g = 1.0 + lambda * (parentg - 1.0);
	f = h + g;
	gotScore = true;

	return f;
}

float Cell::getG() const
{
	return g;
}

Cell* Cell::operator=(const Cell& cell)
{
	this->f = cell.f;
	this->g = cell.g;
	this->gotScore = cell.gotScore;
	this->h = cell.h;
	this->type = cell.type;
	this->posx = cell.posx;
	this->posY = cell.posY;

	return this;
}

bool Cell::isSame(const Cell& cell) const
{
	return (this->posx == cell.posx && this->posY == cell.posY);
	
}
