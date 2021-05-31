#include "TileMap.h"

TileMap::TileMap()
{
	this->loadMap("Level1.txt");
	this->initTilesVector();
}

TileMap::~TileMap()
{
	
}


void TileMap::loadMap(string mapPath)
{
	ifstream openfile(mapPath);

	if (openfile.is_open()) 
	{
		string tileLocation;
		openfile >> tileLocation;
		texture.loadFromFile(tileLocation);
		while (!openfile.eof()) 
		{
			string str;
			openfile >> str;
			char x = str[0], y = str[2];
			if (!isdigit(x) || !isdigit(y))
				map[loadCounter.x][loadCounter.y] = Vector2i(-1, -1);
			else
				map[loadCounter.x][loadCounter.y] = Vector2i(x - '0', y - '0');

			if (openfile.peek() == '\n')
			{
				loadCounter.x = 0;
				loadCounter.y++;
			}
			else
				loadCounter.x++;
		}
		loadCounter.y++;
	}

}

void TileMap::initTilesVector()
{
	for (int i = 0; i < loadCounter.x; i++) {
		vector<Tile*> t;
		for (int j = 0; j < loadCounter.y;j++) {
			t.push_back(new Tile());
		}
		tiles.push_back(t);
	}
}

void TileMap::update()
{
	for (int i = 0; i < loadCounter.x;i++) {
		for (int j = 0; j < loadCounter.y; j++) {
			if (map[i][j].x != -1 && map[i][j].y != -1) {
				rect = IntRect(map[i][j].x * 128, map[i][j].y * 128, 32, 32);
				tiles[i][j] = new Tile(texture, rect, false);
				tiles[i][j]->sprite.setPosition(i * 32, j * 32);
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

void TileMap::render(RenderTarget& target)
{
	for (int i = 0; i < loadCounter.x; i++) {
		for (int j = 0; j < loadCounter.y; j++) {
			target.draw(tiles[i][j]->sprite);
		}
	}
	
}
