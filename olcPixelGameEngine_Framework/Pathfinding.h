#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_

// STL
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <algorithm>

#include "MazeGenerator.h"
// #include "Cell.h"

class Pathfinding : public olc::PixelGameEngine
{
public:
	const float		 UPATE_BUFFER = 0.f;
	static const int GRID_X = 128;
	static const int GRID_Y = 60;
	const olc::Pixel BACKGROUND_COLOUR = olc::BLACK;
protected:
	int cellWidth;
	int cellHeight;

	Cell* Grid[GRID_X][GRID_Y];
	Cell* startNode;
	Cell* endNode;

	bool isFound;
	bool animActive;
	float timeElapsed;

	std::vector<Vector2> dir;
	std::vector<Vector2> dir2;

	std::queue<Cell*> visitQueue;
	std::stack<Cell*> visitStack;
	std::list<Cell*> openList;
	std::list<Cell*> closedList;
public:
	Pathfinding();
	~Pathfinding();

	bool OnUserCreate();
	bool OnUserUpdate(float dt);
	void Render(const float &dt);
	void InputHandler(const float &dt);
	
	virtual void Logic() = 0;
	virtual void CheckNeighbours(Cell* cell) = 0;

	// Helper funcs
	Cell* GetCell(const int &x, const int &y) const;
	Cell* GetCell(const Vector2 &pos)		  const;

	void Clamp(int &val, const int &min, const int &max);
	void GetPosIdx(int &posX, int &posY);

	bool idxIsValid(const int &x, const int &y) const;
	bool idxIsValid(const Vector2 &pos)			const;

	void Reset();
	void PrintPath(Cell* _endNode);
};

#endif

