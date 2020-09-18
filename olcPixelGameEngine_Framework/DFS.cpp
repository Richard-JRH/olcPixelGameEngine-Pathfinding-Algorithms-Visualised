#include "DFS.h"

DFS::DFS()
{
}

DFS::~DFS()
{
	if (curr != nullptr)
	{
		curr = nullptr;
		delete curr;
	}
}

bool DFS::OnUserCreate()
{
	Pathfinding::OnUserCreate();

	isInit = true;
	visitStack = {};

	return true;
}

bool DFS::OnUserUpdate(float dt)
{
	Pathfinding::OnUserUpdate( dt );

	return true;
}

void DFS::Logic()
{
	if (isInit == false)
	{
		if (visitStack.empty() == false)
		{
			curr = visitStack.top();
			curr->SetState( Cell::STATE::VISITED );
			visitStack.pop();

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
		visitStack = {};
		CheckNeighbours( startNode );
		isInit = false;
	}
}

void DFS::CheckNeighbours(Cell* cell)
{
	for (int i = 0; i < dir.size(); ++i)
	{
		Vector2 pos = cell->GetPos() + dir[i];

		if (idxIsValid( pos ))
		{
			Cell* ptr = GetCell( pos );

			// Check if can move diagonally
			//if (i % 2 == 0)
			//{
			//	int idx1 = i - 1;
			//	int idx2 = i + 1;
			//
			//	// Edge case
			//	if (idx1 < 0) idx1 = 7;
			//	if (idx2 < 0) idx2 = 7;
			//
			//	Vector2 check[2];
			//
			//	check[0] = cell->GetPos() + dir[ idx1 ];
			//	check[1] = cell->GetPos() + dir[ idx2 ];
			//
			//	if (idxIsValid(check[0]) && idxIsValid(check[1]))
			//	{
			//		if (GetCell(check[0])->GetState() == Cell::STATE::OBSTACLE ||
			//			GetCell(check[1])->GetState() == Cell::STATE::OBSTACLE)
			//		{
			//			continue;
			//		}
			//	}
			//}

			if (ptr != nullptr &&
			   (ptr->GetState() == Cell::STATE::NIL ||
				ptr->GetState() == Cell::STATE::END))
			{
				switch (ptr->GetState())
				{
					case Cell::STATE::NIL:
					{
						ptr->SetState( Cell::STATE::QUEUED );
						ptr->SetPrev( cell );
						visitStack.push( ptr );
						break;
					}
					case Cell::STATE::END:
					{
						ptr->SetPrev( cell );
						isFound = true;
						animActive = false;
						break;
					}
					default:
					{
						std::cout << "Error in CheckNeighbours() code in DFS " << std::endl;
						break;
					}
				}
			}
		}
	}
}
