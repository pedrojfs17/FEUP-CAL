/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
    searching = false;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
    searching = true;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
    // Initialize Visited in the first time
    if (!searching)
        initializeVisited();

    // Check if already visited
    if (visited[x][y])
        return false;
    else
        visited[x][y] = true;

    // Check the solution
    if (labirinth[x][y] == 2)
        return true;

    // Check if it is a wall or out of borders
    if (labirinth[x][y] == 0 || x < 0 || x > 9 || y < 0 || y > 9)
        return false;

    return (findGoal(x+1,y) || findGoal(x-1,y) || findGoal(x,y+1) || findGoal(x,y-1));
}

/* 1.b) Tempo de execução no pior caso (pesquisa exaustiva do espaço de estados) é determinado pela dimensão do espaço
 * de estados, que muitas vezes é exponencial. 
 */

