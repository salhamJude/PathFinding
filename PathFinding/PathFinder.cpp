#include "PathFinder.h"

PathFinder::PathFinder(Init* init) : init(init), cost(1.0), lambda(0.5),D(1),D2(sqrt(2))  {
    srand(time(NULL));
    roads = 0;
    // Allocate memory for the 'cells' 2D array based on the grid size
    cells = new Cell * [init->getGridsize()];
    for (int i = 0; i < init->getGridsize(); ++i) {
        Cell* c = new Cell[init->getGridsize()];

        for (size_t j = 0; j < init->getGridsize(); j++) {
            // Initialize each cell with its position
            c[j] = Cell(i, j,init->getGrid()[i][j]);
            if (init->getGrid()[i][j] == ROAD) {
                roads++;
            }
        }
        cells[i] = c;
    }
    if (findPath(init->getGrid(), init->getStartPosition()[0], init->getStartPosition()[1], init->getGoalPosition()[0], init->getGoalPosition()[1])) {
        init->drawGrid();
        std::cout << "Path found\n";
    }
    else {
        std::cout << "Path does not exist\n";
    }
}

PathFinder::~PathFinder()
{
	delete cells;
}

bool PathFinder::findPath(GridElement** grid, int sposX, int sposY, int gposX, int gposY)
{
    visited = 0;
    int z = 0;
    int n = 1;
    int current = 0;
    bool found = false;
    struct Path source;
    struct Path *reached = new Path;
    source.x = sposX;
    source.y = sposY;
    source.parent = NULL;
    paths = new Path[roads];

    paths[0] = source;
    
    // Cell start = Cell(sposX, sposY, INITIAL);
    // Cell goal = Cell(gposX, gposY, GOAL);

    int di[4][2] = { {-1,0},//up
					{1, 0},//down
					{0, 1},//right
					{0,-1} //left   
                  };

    while (visited < roads && found != true) {
        z = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                if (paths[i + current].x + di[j][0] >= 0 && paths[i + current].x + di[j][0] < init->getGridsize() && paths[i + current].y + di[j][0] >= 0 && paths[i + current].y + di[j][0] < init->getGridsize()) {
                    if (cells[paths[i + current].x + di[j][0]][paths[i + current].y + di[j][1]].getType() == GOAL) {
                        found = true;
                        reached->parent = &paths[i + current];
                        reached->x = paths[i + current].x;
                        reached->y = paths[i + current].y;
                        break;
                    }
                    else if (cells[paths[i + current].x + di[j][0]][paths[i + current].y + di[j][1]].getType() == ROAD) {
                        struct Path p;
                        p.parent = &paths[i + current];
                        p.x = paths[i + current].x + di[j][0];
                        p.y = paths[i + current].y + di[j][1];
                        paths[visited + 1] = p;
                        cells[paths[i + current].x + di[j][0]][paths[i + current].y + di[j][1]].setType(VISITED);
                        grid[paths[i + current].x + di[j][0]][paths[i + current].y + di[j][1]] = VISITED;
                        z++;
                        visited++;
                    }
                }
            }
            if (found == true) break;
        }
        if (z == 0 || found == true) {
            break;
        }
        current += n;
        n = z;
    }

    if (found) {
        while (reached->parent != NULL) {
            cells[reached->x][reached->y].setType(PATH);
            grid[reached->x][reached->y] = PATH;
            reached = reached->parent;
        }
    }

    return found;
}

void PathFinder::showPaths()
{
    for (int i = 0; i < roads; i++) {
        if (paths[i].parent == nullptr && i != 0) {
            break;
        }
        else {
            std::cout << "x " << paths[i].x << ",y  " << paths[i].y;
        }
        if(paths[i].parent != nullptr){
            std::cout << " parent x " << paths[i].parent->x << ",parent y  " << paths[i].parent->y << std::endl;
        }
    }
}


