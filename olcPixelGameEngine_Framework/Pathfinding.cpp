#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
}

Pathfinding::~Pathfinding()
{
	if (startNode != nullptr)
	{
		startNode = nullptr;
		delete startNode;
	}

	if (endNode != nullptr)
	{
		endNode = nullptr;
		delete endNode;
	}

	for (int x = 0; x < GRID_X; ++x)
		for (int y = 0; y < GRID_Y; ++y)
			if (Grid[x][y] != nullptr)
			{
				Grid[x][y] = nullptr;
				delete Grid[x][y];
			}
}

bool Pathfinding::OnUserCreate()
{
	// Precompute cell(s) length and width
	cellWidth = (ScreenWidth() / GRID_X) - 2;
	cellHeight = (ScreenHeight() / GRID_Y) - 2;

	// Init direction array
	Vector2 vec2;
	dir =
	{
		vec2.Up(),      
		vec2.Right(),  
		vec2.Down(),
		vec2.Left(),
	};
	dir2 =
	{
		vec2.UpLeft(),
		vec2.Up(),
		vec2.UpRight(),
		vec2.Right(),
		vec2.BotRight(),
		vec2.Down(),
		vec2.BotLeft(), 
		vec2.Left(),
	};

	// Init Grid
	for (int x = 0; x < GRID_X; ++x)
		for (int y = 0; y < GRID_Y; ++y)
		{
			Grid[x][y] = new Cell( x, y, Cell::STATE::NIL );

			Vector2 pos( x, y );

			for (int i = 0; i < dir.size(); ++i)
			{
				Vector2 neighbourIdx = pos + dir[i];

				if (idxIsValid( neighbourIdx ))
				{
					Cell* ptr = GetCell( neighbourIdx );
					Grid[x][y]->SetNeighbour( i, ptr );
				}
			}
		}

	// Init start and end node
	startNode = Grid[1][1];
	startNode->SetState( Cell::STATE::START );

	endNode = Grid[GRID_X - 2][GRID_Y - 2];
	endNode->SetState( Cell::STATE::END );

	isFound = false;
	animActive = false;
	timeElapsed = 0.f;

	return true;
}

bool Pathfinding::OnUserUpdate(float dt)
{
	InputHandler( dt );
	Render( dt );

	if (animActive && timeElapsed >= UPATE_BUFFER &&
		startNode != nullptr && endNode != nullptr)
	{
		Logic();
		timeElapsed = 0.f;
	}

	timeElapsed += dt;

	if ( isFound )
	{
		PrintPath( endNode );
	}

	//  DEBUG
	// animActive ? std::cout << "Active " << std::endl : std::cout << "In-active " << std::endl;
	//
	//if (timeElapsed > 0.2f)
	//{
	//	// animActive ? std::cout << "Active " << std::endl : std::cout << "In-active " << std::endl;
	//	// std::cout << visitQueue.size() << std::endl; 
	//	timeElapsed = 0.f;
	//}

	return true;
}

void Pathfinding::Render(const float& dt)
{
	// Draw Grid
	for (int y = 0; y < GRID_Y; ++y)
		for (int x = 0; x < GRID_X; ++x)
			FillRect( (x * (cellWidth + 2)) + 1, 
					  (y * (cellHeight + 2)) + 1, 
					   cellWidth, cellHeight, 
					   Grid[x][y]->GetCellColour());
}

void Pathfinding::InputHandler(const float &dt)
{
	// LMB - Put down obstacle
	if (GetMouse(0).bHeld)
	{
		int posX = GetMouseX();
		int posY = GetMouseY();

		GetPosIdx( posX, posY );

		if (Grid[posX][posY]->GetState() == Cell::STATE::NIL)
			Grid[posX][posY]->SetState( Cell::STATE::OBSTACLE );
	}
	// RMB - Remove obstacle
	if (GetMouse(1).bHeld)
	{
		int posX = GetMouseX();
		int posY = GetMouseY();

		GetPosIdx(posX, posY);

		if (Grid[posX][posY]->GetState() == Cell::STATE::OBSTACLE)
			Grid[posX][posY]->SetState( Cell::STATE::NIL );
	}
	// Q - Put down start node
	if (GetKey(olc::Key::Q).bPressed)
	{
		int posX = GetMouseX();
		int posY = GetMouseY();

		GetPosIdx(posX, posY);

		if (startNode != nullptr)
		{
			startNode->SetState( Cell::STATE::NIL );
			startNode = nullptr;
		}
		if (Grid[posX][posY]->GetState() == Cell::STATE::NIL)
		{
			Grid[posX][posY]->SetState( Cell::STATE::START );
			startNode = Grid[posX][posY];
		}
	}
	// E - Put down end node
	if (GetKey(olc::Key::E).bPressed)
	{
		int posX = GetMouseX();
		int posY = GetMouseY();

		GetPosIdx(posX, posY);

		if (endNode != nullptr)
		{
			endNode->SetState( Cell::STATE::NIL );
			endNode = nullptr;
		}
		if (Grid[posX][posY]->GetState() == Cell::STATE::NIL)
		{
			Grid[posX][posY]->SetState( Cell::STATE::END );
			endNode = Grid[posX][posY];
		}
	}
	// P - Clear all
	if (GetKey(olc::Key::P).bPressed)
	{
		Reset();
	}
	// Space - Start pathfinding
	if (GetKey(olc::Key::SPACE).bPressed)
	{
		animActive = !animActive;
	}
	// M - Maze generation
	if (GetKey(olc::Key::M).bPressed)
	{
		// Get size of graph/grid
		int gridSize = GRID_X * GRID_Y;

		// Fill the board with obstacles first
		for (int x = 0; x < GRID_X; ++x)
			for (int y = 0; y < GRID_Y; ++y)
				Grid[x][y]->SetState( Cell::STATE::OBSTACLE );

		// Set
		std::vector<Cell*> Set;

		// Choose arbitrary vertex
		/*
			TODO : May generate invalid position
		*/
		int randX = rand() % (GRID_X - 1);
		int randY = rand() % (GRID_Y - 1);

		int randDir = rand() % 4;
		Vector2 pos = Vector2(randX, randY) + dir[randDir];

		if (idxIsValid( pos ))
		{
			Cell* temp = GetCell( pos );
			Set.push_back( temp );
		}

		while ( Set.size() < gridSize)
		{
			randDir = rand() % 4;
		}
	}
}

/*
	HELPER FUNCTIONS
*/
Cell* Pathfinding::GetCell(const int &x, const int &y) const
{
	return Grid[x][y];
}

Cell* Pathfinding::GetCell(const Vector2 &pos) const
{
	return Grid[pos.x][pos.y];
}

void Pathfinding::Clamp(int &val, const int &min, const int &max)
{
	if ( val < min ) val = min;
	if ( val > max ) val = max;
}

void Pathfinding::GetPosIdx(int &posX, int &posY)
{
	int x = posX / (cellWidth + 2);
	int y = posY / (cellHeight + 2);

	posX = x;
	posY = y;

	Clamp( posX, 0, GRID_X - 1 );
	Clamp( posY, 0, GRID_Y - 1 );
}

bool Pathfinding::idxIsValid(const int& x, const int& y) const
{
	return ( x >= 0 && x < GRID_X &&
			 y >= 0 && y < GRID_Y );
}

bool Pathfinding::idxIsValid(const Vector2 &pos) const
{
	return ( pos.x >= 0 && pos.x < GRID_X &&
			 pos.y >= 0 && pos.y < GRID_Y );
}

void Pathfinding::Reset()
{
	Clear( olc::BLACK );

	if (startNode != nullptr) startNode = nullptr;
	if (endNode   != nullptr) endNode   = nullptr;

	for (int y = 0; y < GRID_Y; ++y)
		for (int x = 0; x < GRID_X; ++x)
		{
			Grid[x][y]->SetState( Cell::STATE::NIL );
			Grid[x][y]->SetVisited( false );
			Grid[x][y]->SetPrev( nullptr );
			Grid[x][y]->SetDist( 0.f );

			visitQueue = {};
			visitStack = {};
			openList.clear();
		}

	startNode = Grid[1][1];
	startNode->SetState(Cell::STATE::START);

	endNode = Grid[GRID_X - 2][GRID_Y - 2];
	endNode->SetState(Cell::STATE::END);

	isFound	   = false;
	animActive = false;
	timeElapsed = 0.f;
}

void Pathfinding::PrintPath(Cell* _endNode)
{
	Cell* temp = _endNode;

	while (temp != startNode)
	{
		/*if (temp != nullptr)
		{
			if (temp->GetState() != Cell::STATE::START && 
				temp->GetState() != Cell::STATE::END)
			{
				temp->SetState( Cell::STATE::PATH );
			}
		}*/

		Cell* temp2 = temp->GetPrev();

		if ( temp2 != nullptr )
		{
			Vector2 p1( temp->GetX(), temp->GetY() );
			Vector2 p2( temp2->GetX(), temp2->GetY() );

			DrawLine((float)p1.x * (float)(cellWidth + 2.f)  + ((float)cellWidth / 2.f), 
					 (float)p1.y * (float)(cellWidth + 2.f)  + ((float)cellHeight / 2.f),
					 (float)p2.x * (float)(cellHeight + 2.f) + ((float)cellWidth / 2.f),
					 (float)p2.y * (float)(cellHeight + 2.f) + ((float)cellHeight / 2.f),
					 olc::YELLOW);
		}

		temp = temp2;
	}

	for (int y = 0; y < GRID_Y; ++y)
		for (int x = 0; x < GRID_X; ++x)
		{
			if (Grid[x][y]->GetState() == Cell::STATE::QUEUED)
				Grid[x][y]->SetState( Cell::STATE::VISITED );
		}
}

