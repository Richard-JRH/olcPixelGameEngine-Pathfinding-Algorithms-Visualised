#define OLC_PGE_APPLICATION

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 600
#define PIXEL_SIZE	  2

#include <ctime>
#include <time.h>

#include "BFS.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "AStar.h"

void main()
{
	srand( time(NULL) );

	Pathfinding* Scene = new AStar();

	if (Scene->Construct( WINDOW_WIDTH, WINDOW_HEIGHT, PIXEL_SIZE, PIXEL_SIZE ))
		Scene->Start();

	Scene = NULL;
	delete Scene;
}