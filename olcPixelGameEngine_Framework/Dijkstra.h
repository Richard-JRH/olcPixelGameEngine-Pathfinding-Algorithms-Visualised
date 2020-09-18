#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "Pathfinding.h"

class Dijkstra : public Pathfinding
{
private:
	Cell* curr;
	bool isInit;
public:
	Dijkstra();
	~Dijkstra();

	bool OnUserCreate();
	bool OnUserUpdate(float dt);

	void Logic();
	void CheckNeighbours(Cell* cell);
	void Init();
};

#endif

