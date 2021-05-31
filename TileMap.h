#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Tile.h"

using namespace std;
class TileMap
{
private:
	Texture texture;
	Sprite groundSprite;
	IntRect rect;
	Vector2i map[100][100];
	//Vector2i loadCounter = Vector2i(0, 0);
	//vector<vector<Tile*>> tiles;

public:
	vector<vector<Tile*>> tiles;
	Vector2i loadCounter = Vector2i(0, 0);

	TileMap();
	~TileMap();

	//Functions
	void loadMap(string mapPath);
	void initTilesVector();

	void update();
	void render(RenderTarget& target);
};

