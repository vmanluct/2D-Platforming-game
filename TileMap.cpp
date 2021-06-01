#include "TileMap.h"

/*
	Constructor
	Load map from input to see where tiles are on screen
	Initialize all tiles in 2D array with default tile constructor
*/
TileMap::TileMap(string mapPath)
{
	this->loadMap(mapPath);	//load given map
	this->initTilesVector(); //initialize 2D array
}

/*
	Destructor
*/
TileMap::~TileMap()
{
	
}


/*
	Load map for positions of all tiles
	string is file path for txt file of level
*/
void TileMap::loadMap(string mapPath)
{
	ifstream openfile(mapPath); //open file

	if (openfile.is_open()) 
	{
		string tileLocation; //file path for texture sheet
		openfile >> tileLocation;
		texture.loadFromFile(tileLocation); //load texture sheet
		while (!openfile.eof()) //read through whole file
		{
			string str; //read each string in file, format x,x
			openfile >> str;
			char x = str[0], y = str[2]; //x and y position for tile
			if (!isdigit(x) || !isdigit(y)) //if there is not a digit there will be no tile
				map[loadCounter.x][loadCounter.y] = Vector2i(-1, -1);
			else
				map[loadCounter.x][loadCounter.y] = Vector2i(x - '0', y - '0'); //set tile at postion

			if (openfile.peek() == '\n') //check if reached end of the row
			{
				loadCounter.x = 0; //reset column to 0
				loadCounter.y++; //increment what row you are reading
			}
			else
				loadCounter.x++; //have not reached end of row, increment column
		}
		loadCounter.y++;
	}

}

/*
	Initialize all tiles with default tile constructor
*/
void TileMap::initTilesVector()
{
	//go through all rows and columns of map 2D array
	for (int i = 0; i < loadCounter.x; i++) {
		vector<Tile*> t; //initialize vector of tiles
		for (int j = 0; j < loadCounter.y;j++) {
			t.push_back(new Tile()); //create default tile in vector
		}
		tiles.push_back(t); //add vector to vector of vectors
	}
}

/*
	Set sprites and position for all tiles loaded from map
*/
void TileMap::update()
{
	//Go through entire 2D array map
	for (int i = 0; i < loadCounter.x;i++) {
		for (int j = 0; j < loadCounter.y; j++) {
			//if digits were found when loading map set tile at that position with texture
			if (map[i][j].x != -1 && map[i][j].y != -1) {
				rect = IntRect(map[i][j].x * 128, map[i][j].y * 128, 64, 64);
				tiles[i][j] = new Tile(texture, rect, false);
				tiles[i][j]->sprite.setPosition(i * 64, j * 64);
			}
			/*else
			{
				rect = IntRect(128, 128, 64, 64);
				tiles[i][j] = new Tile(texture, rect, false);
				tiles[i][j]->sprite.setPosition(i * 64, j * 64);
			}*/
		}
	}
}

/*
	Draw all tiles to screen
*/
void TileMap::render(RenderTarget& target)
{
	//Go through entire 2D array map
	for (int i = 0; i < loadCounter.x; i++) {
		for (int j = 0; j < loadCounter.y; j++) {
			target.draw(tiles[i][j]->sprite); //draw tile at that position in 2D array
		}
	}
	
}
