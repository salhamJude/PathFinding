#include <iostream>
#include "Init.h"
#include "PathFinder.h"

int main() {
	
	Init* init = new Init();
	PathFinder* pathfinder = new PathFinder(init);
	system("pause");
	return 0;
 }