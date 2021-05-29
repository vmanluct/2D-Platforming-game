#pragma once
#include <SFML/Graphics.hpp>
#include "gameTile.h"
#include <vector>

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

using namespace sf;
class gameWorld
{
	Vector2i exitPos;
	Vector2i playerPos;
	std::vector<Vector2i> enemyPositions;
	void setUpInitialState();
	void setUpEnemyPositions();
	void setUpTiles();

public:
	std::vector<std::vector<gameTile*>> tiles;
	int gridLength;
	gameWorld();
};

#endif // !GAMEWORLD_H

