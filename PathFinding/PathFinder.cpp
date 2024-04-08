#include "PathFinder.h"

PathFinder::PathFinder(Init* init) : init(init), cost(0.1), lambda(0.5),D(1),D2(sqrt(2))  {
    srand(time(NULL));
    // Allocate memory for the 'cells' 2D array based on the grid size
    cells = new Cell * [init->getGridsize()];
    for (int i = 0; i < init->getGridsize(); ++i) {
        Cell* c = new Cell[init->getGridsize()];

        for (size_t j = 0; j < init->getGridsize(); j++) {
            // Initialize each cell with its position
            c[j] = Cell(i, j,init->getGrid()[i][j]);
        }
        cells[i] = c;
    }
    if (findPath(init->getGrid(), init->getStartPosition()[0], init->getStartPosition()[1], init->getGoalPosition()[0], init->getGoalPosition()[1])) {
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
    Cell start = Cell(sposX, sposY,INITIAL);
    Cell current = Cell(sposX, sposY,INITIAL);
    Cell goal = Cell(gposX, gposY,GOAL);
    Direction di;
    bool canContinue = true;
    bool found = false;
    float scores[8];
    int pos[8][2];
    int update[2] = { 0,0 };

    while (canContinue)
    {
        //Left
        if (current.getYposition() - 1 >= 0 && grid[current.getXposition()][current.getYposition() - 1] != WALL && grid[current.getXposition()][current.getYposition() - 1] != PATH) {
            scores[0] = cells[current.getXposition()][current.getYposition() - 1].calculateScore(cost,lambda,gposX,gposY,current.getG(), D, D2);
        }
        else {
            scores[0] = -1.0;
        }
        pos[0][0] = current.getXposition();
        pos[0][1] = current.getYposition() - 1;

        //Down
        if (current.getXposition() + 1 < init->getGridsize() && grid[current.getXposition() + 1][current.getYposition()] != WALL && grid[current.getXposition() + 1][current.getYposition()] != PATH) {
            scores[1] = cells[current.getXposition() + 1][current.getYposition()].calculateScore(cost, lambda, gposX, gposY, current.getG(), D, D2);
        }
        else {
            scores[1] = -1.0;
        }
        pos[1][0] = current.getXposition() + 1;
        pos[1][1] = current.getYposition();

        //Right
        if (current.getYposition() + 1 < init->getGridsize() && grid[current.getXposition()][current.getYposition() + 1] != WALL && grid[current.getXposition()][current.getYposition() + 1] != PATH) {
            scores[2] = cells[current.getXposition()][current.getYposition() + 1].calculateScore(cost, lambda, gposX, gposY, current.getG(), D, D2);
        }
        else {
            scores[2] = -1.0;
        }
        pos[2][0] = current.getXposition();
        pos[2][1] = current.getYposition() + 1;

        //Up
        if (current.getXposition() - 1 >= 0 && grid[current.getXposition() - 1][current.getYposition()] != WALL && grid[current.getXposition() - 1][current.getYposition()] != PATH) {
            scores[3] = cells[current.getXposition() - 1][current.getYposition()].calculateScore(cost, lambda, gposX, gposY, current.getG(), D, D2);
        }
        else {
            scores[3] = -1.0;
        }
        pos[3][0] = current.getXposition() - 1;
        pos[3][1] = current.getYposition();

        //upLeft
        if (current.getXposition() - 1 >= 0 && current.getYposition() - 1 >= 0 && grid[current.getXposition() - 1][current.getYposition() - 1] != WALL && grid[current.getXposition() - 1][current.getYposition() - 1] != PATH ) {
            if (grid[current.getXposition() - 1][current.getYposition()] != WALL && grid[current.getXposition() - 1][current.getYposition()] != PATH && grid[current.getXposition()][current.getYposition() - 1] != WALL && grid[current.getXposition()][current.getYposition() - 1] != PATH) {
                scores[4] = cells[current.getXposition() - 1][current.getYposition() - 1].calculateScore(cost, lambda, gposX, gposY, current.getG(), D, D2);
            }
            else {
                scores[4] = -1.0;
            }
			
		}
        else {
			scores[4] = -1.0;
		}
        pos[4][0] = current.getXposition() - 1;
        pos[4][1] = current.getYposition() - 1;

        //upRight
        if (current.getXposition() - 1 >= 0 && current.getYposition() + 1 < init->getGridsize() && grid[current.getXposition() - 1][current.getYposition() + 1] != WALL && grid[current.getXposition() - 1][current.getYposition() + 1] != PATH) {
            if (grid[current.getXposition() - 1][current.getYposition()] != WALL && grid[current.getXposition() - 1][current.getYposition()] != PATH && grid[current.getXposition()][current.getYposition() + 1] != WALL && grid[current.getXposition()][current.getYposition() + 1] != PATH)
            {
				scores[5] = cells[current.getXposition() - 1][current.getYposition() + 1].calculateScore(cost, lambda, gposX, gposY, current.getG(), D, D2);
			}
            else{
				scores[5] = -1.0;
			}
        }
        else
        {
            scores[5] = -1.0;
        }
        pos[5][0] = current.getXposition() - 1;
        pos[5][1] = current.getYposition() + 1;

        //downLeft
        if (current.getXposition() + 1 < init->getGridsize() && current.getYposition() - 1 >= 0 && grid[current.getXposition() + 1][current.getYposition() - 1] != WALL && grid[current.getXposition() + 1][current.getYposition() - 1] != PATH) {
            if (grid[current.getXposition() + 1][current.getYposition()] != WALL && grid[current.getXposition() + 1][current.getYposition()] != PATH && grid[current.getXposition()][current.getYposition() - 1] != WALL && grid[current.getXposition()][current.getYposition() - 1] != PATH) {
                scores[6] = cells[current.getXposition() + 1][current.getYposition() - 1].calculateScore(cost, lambda, gposX, gposY, current.getG(), D, D2);
            }else {
                scores[6] = -1.0;
            }
		}
        else {
			scores[6] = -1.0;
		}
        pos[6][0] = current.getXposition() + 1;
        pos[6][1] = current.getYposition() - 1;

        //downRight
        if (current.getXposition() + 1 < init->getGridsize() && current.getYposition() + 1 < init->getGridsize() && grid[current.getXposition() + 1][current.getYposition() + 1] != WALL && grid[current.getXposition() + 1][current.getYposition() + 1] != PATH) {
            if (grid[current.getXposition() + 1][current.getYposition()] != WALL && grid[current.getXposition() + 1][current.getYposition()] != PATH && grid[current.getXposition()][current.getYposition() + 1] != WALL && grid[current.getXposition()][current.getYposition() + 1] != PATH) {
                scores[7] = cells[current.getXposition() + 1][current.getYposition() + 1].calculateScore(cost, lambda, gposX, gposY, current.getG(), D, D2);
            }
            else {
                scores[7] = -1.0;
            }
        }
        else {
			scores[7] = -1.0;
		}
        pos[7][0] = current.getXposition() + 1;
        pos[7][1] = current.getYposition() + 1;


        if (scores[0] == -1.0 && scores[1] == -1.0 && scores[2] == -1.0 && scores[3] == -1.0 && scores[4] == -1.0 && scores[5] == -1.0 && scores[6] == -1.0 && scores[7] == -1.0) {
            found = false;
            break;
        }
        di = winner(scores,pos,gposX,gposY);
        switch (di)
        {
        case UP:
            update[0] = -1;
            update[1] = 0;
            break;
        case LEFT:
            update[0] = 0;
            update[1] = -1;
            break;
        case DOWN:
            update[0] = 1;
            update[1] = 0;
            break;
        case RIGHT:
            update[0] = 0;
            update[1] = 1;
            break;
        case UPLELFT:
			update[0] = -1;
			update[1] = -1;
			break;
        case UPRIGHT:
            update[0] = -1;
            update[1] = 1;
            break;
        case DOWNLEFT:
            update[0] = 1;
			update[1] = -1;
			break;
        case DOWNRIGHT:
		    update[0] = 1;
		    update[1] = 1;
		    break;
        default:
            break;
        }
        
        if (current.isSame(goal)) {
            found = true;
            canContinue = false;
        }
        else {
            if (!current.isSame(start)) {
                grid[current.getXposition()][current.getYposition()] = PATH;
            }
            current = cells[current.getXposition() + update[0]][current.getYposition() + update[1]];
        }
        init->drawGrid();
        Sleep(50);
    }
     
    return found;
}

Direction PathFinder::winner(float* scores, int pos[8][2], int gposX, int gposY)
{
    int less = 0;
    float score = 0.0;
    for (size_t i = 0; i < 8; i++)
    {
        if (scores[i] == -1.0) {
            continue;
        }
        less = i;
        score = scores[i];
    }

    for (size_t i = 0; i < 4; i++)
    {   
        if (scores[i] == score && i != less) {
            int r = 1 + rand() % (2 - 1 + 1 );
            if (r != 1) {
                less = i;
                score = scores[i];
            }

        }
        else if (scores[i] < score && scores[i] >= 0.0 ) {
            less = i;
            score = scores[i];
        }
    }
    switch (less)
    {
    case 0 :
        return LEFT;
        break;
    case 1:
        return DOWN;
        break;
    case 2:
        return RIGHT;
        break;
    case 3:
        return UP;
        break;
    case 4:
        return UPLELFT;
		break;
    case 5:
		return UPRIGHT;
		break;
    case 6:
         return DOWNLEFT;
         break;
    case 7:
        return DOWNRIGHT;
		break;
    default:
        break;
    }
}
