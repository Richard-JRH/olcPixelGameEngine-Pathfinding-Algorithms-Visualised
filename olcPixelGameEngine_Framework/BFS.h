#ifndef _BREADTH_FIRST_SEARCH_H_
#define _BREADTH_FIRST_SEARCH_H_

#include "Pathfinding.h"

class BFS : public Pathfinding
{
private:
	Cell* curr;
	bool isInit;
public:
	BFS();
	~BFS();

	bool OnUserCreate();
	bool OnUserUpdate(float dt);
	
	void Logic();
	void CheckNeighbours(Cell* cell);
};

#endif
