#ifndef _CELL_H_
#define _CELL_H_

#include "olcPixelGameEngine.h"
#include "Vector2.h"

class Cell
{
private:
	const olc::Pixel NIL_COLOUR		 = olc::BLACK;
	const olc::Pixel OBSTACLE_COLOUR = olc::WHITE;
	const olc::Pixel START_COLOUR	 = olc::RED;
	const olc::Pixel END_COLOUR		 = olc::BLUE;
	const olc::Pixel QUEUED_COLOUR	 = olc::GREEN;
	const olc::Pixel VISITED_COLOUR	 = olc::VERY_DARK_GREY;
	const olc::Pixel PATH_COLOUR	 = olc::YELLOW;
public:
	enum STATE
	{
		NIL, 
		OBSTACLE, 
		START,
		END,
		QUEUED, 
		VISITED,
		PATH,

		NUM_STATE
	};
private:
	Vector2 pos;
	Cell::STATE state;
	bool isVisited;
	float dist;

	float fCost; // Final cost - globalCost + heuristic
	float gCost; // Global cost - dist from start node
	float hCost; // Heuristic - dist from end node

	Cell* neighbours[4];
	Cell* prev;
public:
	Cell();
	Cell(int _x, int _y);
	Cell(int _x, int _y, Cell::STATE _state);
	~Cell();

	// Getters/Setters
	void SetState(Cell::STATE _state);
	Cell::STATE GetState() const;

	void SetVisited(bool _visited);
	bool IsVisited() const;

	void SetXY(int _x, int _y);
	void SetX(int _x);
	void SetY(int _y);

	int GetX()		 const;
	int GetY()		 const;
	Vector2 GetPos() const;

	void SetDist(float _dist);
	float GetDist();

	float GetFCost() const;
	float GetGCost() const;
	float GetHCost() const;

	void SetFCost(float _fCost);
	void SetGCost(float _gCost);
	void SetHCost(float _hCost);

	void SetPrev(Cell* _prev);
	Cell* GetPrev() const;

	void SetNeighbour(int _idx, Cell* _ptr);
	Cell* GetNeighbour(const int &_idx) const;

	olc::Pixel GetCellColour() const;
};

#endif
