#include "gameWorld.h"

void gameWorld::setUpInitialState()
{
	exitPos = Vector2i(1, 0);
	playerPos = Vector2i(gridLength - 1, gridLength - 1);
	setUpEnemyPositions();
	setUpTiles();
}

void gameWorld::setUpEnemyPositions()
{
	enemyPositions.clear();
	enemyPositions.push_back(Vector2i(0, 2));
	enemyPositions.push_back(Vector2i(6, 0));
	enemyPositions.push_back(Vector2i(2, 7));
}

void gameWorld::setUpTiles()
{
	tiles.clear();
	std::vector<gameTile*> firstRow;
	firstRow.push_back(new gameTile("images/", 0, 0, false, false));
	firstRow.push_back(new gameTile("images/", 50, 0, true, true));
	firstRow.push_back(new gameTile("images/", 100, 0, false, false));
	firstRow.push_back(new gameTile("images/", 150, 0, false, false));
	firstRow.push_back(new gameTile("images/", 200, 0, false, false));
	firstRow.push_back(new gameTile("images/", 250, 0, false, false));
	firstRow.push_back(new gameTile("images/", 300, 0, true, false));
	firstRow.push_back(new gameTile("images/", 350, 0, false, false));
	tiles.push_back(firstRow);
}

gameWorld::gameWorld()
{
	gridLength = 8;
	setUpInitialState();
}
