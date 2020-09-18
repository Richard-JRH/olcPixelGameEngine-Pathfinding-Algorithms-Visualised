#include "Dijkstra.h"

Dijkstra::Dijkstra()
{
}

Dijkstra::~Dijkstra()
{
}

bool Dijkstra::OnUserCreate()
{
	Pathfinding::OnUserCreate();

	isInit = true;
	visitQueue = {};

	return true;
}

bool Dijkstra::OnUserUpdate(float dt)
{
	Pathfinding::OnUserUpdate( dt );

	return true;
}

void Dijkstra::Logic()
{
	if (isInit == false)
	{
		if (visitQueue.empty() == false)
		{
			curr = visitQueue.front();
			curr->SetState( Cell::STATE::VISITED );
			visitQueue.pop();

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

void Dijkstra::CheckNeighbours(Cell* cell)
{
	for (int i = 0; i < 4; ++i)
	{
		Cell* ptr = cell->GetNeighbour( i );

		if (ptr != nullptr &&
		   (ptr->GetState() == Cell::STATE::NIL ||
			ptr->GetState() == Cell::STATE::END))
		{
			switch ( ptr->GetState() )
			{
				case Cell::STATE::NIL:
				{
					// float calcDist = cell->GetDist() + distToAdd;

					// if (calcDist < ptr->GetDist())
					{
						// ptr->SetDist( calcDist );
						ptr->SetPrev( cell );
					}

					ptr->SetState( Cell::STATE::QUEUED );
					visitQueue.push( ptr );
					break;
				}
				case Cell::STATE::END:
				{
					// ptr->SetDist(cell->GetDist() + distToAdd);
					ptr->SetPrev( cell );
					isFound = true;
					animActive = false;
					break;
				}
				default:
				{
					std::cout << "Error in CheckNeighbours() code in Dijkstra " << std::endl;
					break;
				}
			}
		}
	}
}

void Dijkstra::Init()
{
	visitQueue = {};

	for (int x = 0; x < GRID_X; ++x)
		for (int y = 0; y < GRID_Y; ++y)
		{
			Grid[x][y]->SetDist( INFINITY );
			Grid[x][y]->SetPrev( nullptr );
		}

	startNode->SetDist( 0.f );
	CheckNeighbours( startNode );

	isInit = false;
}

