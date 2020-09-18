#ifndef _DEPTH_FIRST_SEARCH_H_
#define _DEPTH_FIRST_SEARCH_H_

#include "Pathfinding.h"

class DFS : public Pathfinding
{
private:
	Cell* curr;
	bool isInit;
public:
	DFS();
	~DFS();

	bool OnUserCreate();
	bool OnUserUpdate(float dt);

	void Logic();
	void CheckNeighbours(Cell* cell);
};

#endif

