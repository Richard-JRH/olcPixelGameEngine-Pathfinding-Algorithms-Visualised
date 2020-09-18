#ifndef _A_STAR_H_
#define _A_STAR_H_

#include "Pathfinding.h"

class AStar : public Pathfinding
{
private:
	Cell* curr;
	bool isInit;
public:
	AStar();
	~AStar();

	bool OnUserCreate();
	bool OnUserUpdate(float dt);

	void Logic();
	void CheckNeighbours(Cell* cell);
	int CalcHeuristic(const Cell* cell);
	Cell* GetMinFCost(std::list<Cell*> cellList);

	void Init();
};

#endif

