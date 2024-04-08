#include "PathFinder.h"

PathFinder::PathFinder(Init* init) : init(init) {
    // Allocate memory for the 'cells' 2D array based on the grid size
    cells = new Cell * [init->getGridsize()];
    for (int i = 0; i < init->getGridsize(); ++i) {
        Cell* c = new Cell[init->getGridsize()];

        for (size_t j = 0; j < init->getGridsize(); j++) {
            // Initialize each cell with its position
            c[j] = Cell(i, j);
        }
        cells[i] = c;
    }

}

PathFinder::~PathFinder()
{
	delete cells;
}

bool PathFinder::findPath(GridElement** grid, int sposX, int sposY, int gposX, int gposY)
{
    Cell start = Cell(sposX, sposY);
    Cell current = Cell(sposX, sposY);
    Cell goal = Cell(gposX, gposY);

    
    return false;
}
