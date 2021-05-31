#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "TileMap.h"


using namespace sf;
class Game
{
private:
	//Window
	RenderWindow window;
	VideoMode videoMode;
	Event ev;

	Player* player;
	TileMap* tile;


	void initWindow();

	void initPlayer();

	void initTileMap();

public:
	//Constructor and Destructor
	Game();
	virtual ~Game();


	//Functions
	void updatePlayer();
	void updateTileMap();
	void updateWallCollision();
	void updateCollision();
	void update();
	void renderPlayer();
	void renderTileMap();
	void render();
	const RenderWindow& getWindow();
};

