#pragma once
#include "Tile.h"
using namespace std;
class TileMap
{
private:
	vector<vector<Tile*>> tiles;

public:
	TileMap();
	~TileMap();

	//Functions
	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);

	void update();
	void render();
};

