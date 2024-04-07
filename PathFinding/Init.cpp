#include "Init.h"


Init::Init() {

	#ifdef _WIN32
		os = OS_WINDOWS;
	#elif __linux__
		os = OS_LINUX;
	#elif __APPLE__
		os = OS_MACOS;
	#elif __unix__
		os = OS_UNIX;
	#endif


	srand(time(NULL));

	do
	{

		std::cout << "Enter the grid size ( >25) :";
		std::cin >> this->gridsize;

	} while (this->gridsize <= 25);
	grid = new GridElement*[gridsize];
	for (int i = 0; i < gridsize; ++i) {
		grid[i] = new GridElement[gridsize];
	}
	initGrid();
	generateWalls(); 
	drawGrid();

	do
	{
		std::cout << "Enter the x coordination of the start position : ";
		std::cin >> start_position[0];
		std::cout << "Enter the y coordination of the start position : ";
		std::cin >> start_position[1];
	} while (start_position[0] >= gridsize or start_position[1] >= gridsize or isWall(start_position[0], start_position[1]));
	setStartPostion(start_position[0], start_position[1]);
	drawGrid();
	do
	{
		std::cout << "Enter the x coordination of the goal position : ";
		std::cin >> start_position[0];
		std::cout << "Enter the y coordination of the goal position : ";
		std::cin >> start_position[1];
	} while (start_position[0] >= gridsize or start_position[1] >= gridsize or isWall(start_position[0], start_position[1]) or isStartPositon(start_position[0], start_position[1]));
	setGoalPosition(start_position[0], start_position[1]);
	drawGrid();
}

void Init::drawGrid()
{
	switch (os) {
	case OS_WINDOWS:
		system("cls");
		break;
	case OS_LINUX:
		system("clear");
		break;
	case OS_MACOS:
		system("clear");
		break;
	case OS_UNIX:
		system("clear");
		break;
	case OS_UNKNOWN:
		break;
	default:
		break;
	}


	
	std::cout << std::endl;
	for (size_t i = 0; i < gridsize; i++)
	{
		std::cout << "|";
		for (size_t j = 0; j < gridsize; j++) {
			if(grid[i][j] == ROAD)
				std::cout << " ";
			else if (grid[i][j] == WALL)
				std::cout << "X";
			else if (grid[i][j] == PATH)
				std::cout << "1";
			else if (grid[i][j] == INITIAL)
				std::cout << "S";
			else if (grid[i][j] == GOAL)
				std::cout << "G";
			std::cout << "|";
		}
		std::cout << std::endl;
	}

}

void Init::generateWalls()
{
	int nbrWall = 10; //0 + rand() % (5 - 0 + 1 - 1);
	int maxwallLength = gridsize / 2 + (gridsize / 4);
	int wallLength, posY, posX;
	Direction dir;
	
	for (size_t i = 0; i < nbrWall; i++)
	{
		posY = 0 + rand() % (gridsize - 0 + 1 - 1);
		posX = 0 + rand() % (gridsize - 0 + 1 - 1);

		wallLength = (maxwallLength / 2) + rand() % (maxwallLength - (maxwallLength / 2) + 1 - 1);

		int x = 1 + rand() % (4 - 0 + 1);
		switch (x)
		{
		case 1:
			dir = UP;
			break;
		case 2:
			dir = LEFT;
			break;
		case 3:
			dir = DOWN;
			break;
		case 4:
			dir = RIGHT;
			break;
		default:
			dir = UP;
			break;
		}
		generateWall(posX, posY, dir, wallLength);
	}
}

void Init::generateWall(int posX, int posY, Direction dir, int length)
{
	bool breach = false;
	for (size_t i = 0; i < length; i++)
	{
		grid[posY][posX] = WALL;
		if (dir == UP) {
			if (posY - 1 == 0) {
				for (size_t i = posY; i < gridsize; i++)
				{
					if (grid[i][posX] == ROAD) {
						breach = true;
						break;
					}
					 
				}
				if (breach) {
					grid[posY - 1][posX] = WALL;
					posY -= 1;
				}
				else {
					break;
				}
			}
			else if(posY - 1 > 0) {
				grid[posY - 1][posX] = WALL;
				posY -= 1;
			}
			else {
				break;
			}
		}
		else if (dir == DOWN) {
			if (posY + 1 == gridsize - 1) {
				for (size_t i = posY; i >= 0; i--)
				{
					if (grid[i][posX] == ROAD) {
						breach = true;
						break;
					}

				}
				if (breach) {
					grid[posY + 1][posX] = WALL;
					posY += 1;
				}
				else {
					break;
				}
			}
			else if (posY + 1 < gridsize - 1) {
				grid[posY + 1][posX] = WALL;
				posY += 1;
			}
			else {
				break;
			}
		}
		else if (dir == LEFT) {
			if (posX - 1 == 0) {
				for (size_t i = posX; i < gridsize; i++)
				{
					if (grid[posY][i] == ROAD) {
						breach = true;
						break;
					}

				}
				if (breach) {
					grid[posY][posX - 1] = WALL;
					posX -= 1;
				}
				else {
					break;
				}
			}
			else if (posX - 1 > 0) {
				grid[posY][posX - 1] = WALL;
				posX -= 1;
			}
			else {
				break;
			}
		}
		else if (dir == RIGHT) {
			if (posX + 1 == gridsize - 1 ) {
				for (size_t i = posX; i  <= 0; i--)
				{
					if (grid[posY][i] == ROAD) {
						breach = true;
						break;
					}

				}
				if (breach) {
					grid[posY][posX + 1] = WALL;
					posX += 1;
				}
				else {
					break;
				}
			}
			else if (posX + 1 < gridsize - 1) {
				grid[posY][posX + 1] = WALL;
				posX += 1;
			}
			else {
				break;
			}
		}
		breach = false;
	}
	
}

void Init::initGrid()
{
	for (size_t i = 0; i < gridsize; i++)
	{
		for (size_t j = 0; j < gridsize; j++)
		{	
			grid[i][j] = ROAD;
		}

	}
}

void Init::setStartPostion(int x, int y)
{
	grid[x][y] = INITIAL;
}

void Init::setGoalPosition(int x, int y)
{
	grid[x][y] = GOAL;
}

bool Init::isWall(int x, int y)
{
	return grid[x][y] == WALL;
}

bool Init::isRoad(int x, int y)
{
	return grid[x][y] == ROAD;
}

bool Init::isPath(int x, int y)
{
	return grid[x][y] == PATH;
}

bool Init::isGoalPosition(int x, int y)
{
	return grid[x][y] == GOAL;
}

bool Init::isStartPositon(int x, int y)
{
	return grid[x][y] == INITIAL;
}
