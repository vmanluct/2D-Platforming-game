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
	Texture texture; //texture sheet containing all types of tiles
	Sprite groundSprite; //sprite for each tile
	IntRect rect; //rectangle for which image in sheet to use
	Vector2i map[520][520]; //2D array to hold data for each tile
	//Vector2i loadCounter = Vector2i(0, 0);
	//vector<vector<Tile*>> tiles;

public:

	vector<vector<Tile*>> tiles; //2D array for all the tiles
	Vector2i loadCounter = Vector2i(0, 0); //used when loading info from map file

	TileMap(string mapPath); //Tile map constructor
	~TileMap(); //Tile map destructor

	//Functions
	void loadMap(string mapPath); //load info from txt file for tiles
	void initTilesVector(); //initialize all tiles in 2d array with default Tile constructor

	void update(); //update sprite, and position of all tiles
	void render(RenderTarget& target); //draw all tile to screen
};

