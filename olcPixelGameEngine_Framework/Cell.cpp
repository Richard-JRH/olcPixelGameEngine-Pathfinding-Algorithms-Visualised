#include "Cell.h"

Cell::Cell()
{
	this->pos = Vector2( 0 );

	this->state = Cell::STATE::NIL;
	this->isVisited = false;

	dist = 0.f;

	fCost = 0.f;
	gCost = 0.f;
	hCost = 0.f;

	for (int i = 0; i < 4; ++i)
		neighbours[i] = nullptr;

	prev = nullptr;
}

Cell::Cell(int _x, int _y)
{
	this->pos = Vector2( _x, _y );

	this->state = Cell::STATE::NIL;
	this->isVisited = false;

	dist = 0.f;

	fCost = 0.f;
	gCost = 0.f;
	hCost = 0.f;

	for (int i = 0; i < 4; ++i)
		neighbours[i] = nullptr;

	prev = nullptr;
}

Cell::Cell(int _x, int _y, Cell::STATE _state)
{
	this->pos = Vector2( _x, _y );

	this->state = _state;
	this->isVisited = false;

	dist = 0.f;

	fCost = 0.f;
	gCost = 0.f;
	hCost = 0.f;

	for (int i = 0; i < 4; ++i)
		neighbours[i] = nullptr;

	prev = nullptr;
}

Cell::~Cell()
{
}


void Cell::SetState(Cell::STATE _state)
{
	this->state = _state;
}

Cell::STATE Cell::GetState() const
{
	return this->state;
}

void Cell::SetVisited(bool _visited)
{
	this->isVisited = _visited;
}

bool Cell::IsVisited() const
{
	return this->isVisited;
}

void Cell::SetXY(int _x, int _y)
{
	this->pos.x = _x;
	this->pos.y = _y;
}

void Cell::SetX(int _x)
{
	this->pos.x = _x;
}

void Cell::SetY(int _y)
{
	this->pos.y = _y;
}

int Cell::GetX() const
{
	return this->pos.x;
}

int Cell::GetY() const
{
	return this->pos.y;
}

Vector2 Cell::GetPos() const
{
	return this->pos;
}

void Cell::SetDist(float _dist)
{
	this->dist = _dist;
}

float Cell::GetDist()
{
	return this->dist;
}

float Cell::GetFCost() const
{
	return this->fCost;
}

float Cell::GetGCost() const
{
	return this->gCost;
}

float Cell::GetHCost() const
{
	return this->hCost;
}

void Cell::SetFCost(float _fCost)
{
	this->fCost = _fCost;
}

void Cell::SetGCost(float _gCost)
{
	this->gCost = _gCost;
}

void Cell::SetHCost(float _hCost)
{
	this->hCost = _hCost;
}

void Cell::SetPrev(Cell* _prev)
{
	this->prev = _prev;
}

Cell* Cell::GetPrev() const
{
	return this->prev;
}

void Cell::SetNeighbour(int _idx, Cell* _ptr)
{
	if ( _idx < 0 || _idx > 3 )
		throw "Cell neighbour index out of range, unable to set ";

	if ( _ptr != nullptr )
		neighbours[_idx] = _ptr;
}

Cell* Cell::GetNeighbour(const int &_idx) const
{
	if ( _idx < 0 || _idx > 3 )
		throw "Cell neighbour index out of range, unable to get ";

	return neighbours[_idx];
}

olc::Pixel Cell::GetCellColour() const
{
	switch ( this->state )
	{
		case STATE::NIL:
		{
			return NIL_COLOUR;
			break;
		}
		case STATE::OBSTACLE:
		{
			return OBSTACLE_COLOUR;
			break;
		}
		case STATE::START:
		{
			return START_COLOUR;
			break;
		}
		case STATE::END:
		{
			return END_COLOUR;
			break;
		}
		case STATE::QUEUED:
		{
			return QUEUED_COLOUR;
			break;
		}
		case STATE::VISITED:
		{
			return VISITED_COLOUR;
			break;
		}
		case STATE::PATH:
		{
			return PATH_COLOUR;
			break;
		}
		default:
		{
			std::cout << "Cell state invalid!! " << std::endl;
			break;
		}
	}
}