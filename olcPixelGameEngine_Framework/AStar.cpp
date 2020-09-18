#include "AStar.h"

AStar::AStar()
{
}

AStar::~AStar()
{
	if (curr != nullptr)
	{
		curr = nullptr;
		delete curr;
	}
}

bool AStar::OnUserCreate()
{
	Pathfinding::OnUserCreate();

	isInit = true;
	openList.clear();
	closedList.clear();

	return true;
}

bool AStar::OnUserUpdate(float dt)
{
	Pathfinding::OnUserUpdate( dt );

	return true;
}

void AStar::Logic()
{
	if (isInit == false)
	{
		if (openList.empty() == false)
		{
			// Get node with the lowest F-cost in the open list
			curr = GetMinFCost( openList );

			// Check if current node is goal node
			if (curr->GetState() == Cell::STATE::END)
			{
				isFound = true;
				animActive = false;
				isInit = true;
				return;
			}

			// Remove node from open list, add to closed list
			openList.remove( curr );
			closedList.push_back( curr );

			if (curr->GetState() != Cell::STATE::START &&
				curr->GetState() != Cell::STATE::END)
			{
				curr->SetState( Cell::STATE::VISITED );
			}

			CheckNeighbours( curr );
		}
		else
		{
			animActive = false;
			isInit = true;
		}
	}
	else
	{
		Init();
	}
}

void AStar::CheckNeighbours(Cell* cell)
{
	for (int i = 0; i < dir2.size(); ++i)
	{
		Cell* childNode = nullptr;
		Vector2 pos = cell->GetPos() + dir2[i];

		if (idxIsValid( pos ))
			childNode = GetCell( pos );

		// Check if can move diagonally
		if (i % 2 == 0)
		{
			int idx1 = i - 1;
			int idx2 = i + 1;

			if (idx1 < 0) idx1 = 7;

			if (idxIsValid(cell->GetPos() + dir2[ idx1 ]) &&
				idxIsValid(cell->GetPos() + dir2[ idx2 ]))
			{
				Cell* check1 = GetCell(cell->GetPos() + dir2[ idx1 ]);
				Cell* check2 = GetCell(cell->GetPos() + dir2[ idx2 ]);

				if (check1->GetState() == Cell::STATE::OBSTACLE &&
					check2->GetState() == Cell::STATE::OBSTACLE)
				{
					continue;
				}
			}
		}

		if (childNode == nullptr) continue;
		if (childNode->GetState() == Cell::STATE::OBSTACLE) continue;
		if (childNode->GetState() == Cell::STATE::END)
		{
			childNode->SetPrev( cell );
			isFound = true;
			animActive = false;
			isInit = true;
			break;
		}

		bool foundClosed = (std::find(closedList.begin(), closedList.end(), childNode) != closedList.end());
		if ( foundClosed ) continue;

		float tmpGCost = cell->GetGCost() + (i % 2 == 0 ?  + 1.41421356237f : 1.f);
		// float tmpGCost = cell->GetGCost() + 1.f;
		if (tmpGCost < childNode->GetGCost())
		{
			childNode->SetPrev( cell );
			childNode->SetGCost( tmpGCost );
			childNode->SetHCost(CalcHeuristic( childNode ));
			childNode->SetFCost( childNode->GetGCost() + childNode->GetHCost() );

			bool foundOpen = (std::find(openList.begin(), openList.end(), childNode) != openList.end());
			openList.push_back( childNode );
			childNode->SetState( Cell::STATE::QUEUED );
		}
	}
}

int AStar::CalcHeuristic(const Cell* cell)
{
	int diffX = abs( cell->GetX() - endNode->GetX() );
	int diffY = abs( cell->GetY() - endNode->GetY() );

	if (diffX == diffY)
		return (diffX * diffX) + (diffY * diffY);

	int remainder = 0;

	if (diffX > diffY)
	{
		remainder = diffX - diffY;
		return sqrt((diffY * diffY) + (diffY * diffY)) + remainder;
	}
	else
	{
		remainder = diffY - diffX;
		return sqrt((diffX * diffX) + (diffX * diffX)) + remainder;
	}
	
	return -1;
	// return ( sqrt(pow(diffX, 2) + pow(diffY, 2)) );
	// return diffX + diffY;
}

Cell* AStar::GetMinFCost(std::list<Cell*> cellList)
{
	float min = FLT_MAX;
	Cell* ret = nullptr;

	for (Cell* &c : cellList)
		if (c->GetFCost() < min)
		{
			min = c->GetFCost();
			ret = c;
		}

	return ret;
}

void AStar::Init()
{
	curr = nullptr;
	openList.clear();
	closedList.clear();

	for (int x = 0; x < GRID_X; ++x)
		for (int y = 0; y < GRID_Y; ++y)
		{
			Grid[x][y]->SetGCost( INFINITY );
			Grid[x][y]->SetHCost( 0.f );
			Grid[x][y]->SetFCost( Grid[x][y]->GetGCost() + Grid[x][y]->GetHCost() );
			Grid[x][y]->SetPrev( nullptr );
		}

	startNode->SetGCost( 0.f );
	startNode->SetHCost(CalcHeuristic( startNode ));
	startNode->SetFCost( startNode->GetGCost() + startNode->GetHCost() );
	openList.push_back( startNode );

	isInit = false;
}
