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

	Player* player; //Player class
	TileMap* tile; //Tiles in level


	void initWindow(); //initialize playable window

	void initPlayer(); //initialize playable character

	void initTileMap(); //initialize tiles in level

public:
	//Constructor and Destructor
	Game();
	virtual ~Game();


	//Functions
	void updatePlayer(); //update attributes of player
	void updateTileMap(); //update what tiles are in the window
	void updateGroundCollision(); //check if player is overlapping the ground and ceiling
	void updateWallCollision(); //check if player is overlapping walls
	void updateCollision(); //check is player has reached bottom or top of window
	void update(); //update all objects in level
	void renderPlayer(); //draw player to screen
	void renderTileMap(); //draw tiles to screen
	void render(); //draw everything to screen
	const RenderWindow& getWindow(); //get the display window
};

