#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Player.h"

using namespace sf;
class Game
{
private:
	//Window
	RenderWindow window;
	VideoMode videoMode;
	Event ev;

	Player* player;

	void initWindow();
	void initPlayer();

public:
	//Constructor and Destructor
	Game();
	virtual ~Game();


	//Functions
	void updatePlayer();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
	const RenderWindow& getWindow();
};

