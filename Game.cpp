#include "Game.h"


/*
	Initialize window where game is played
*/
void Game::initWindow()
{
	this->videoMode.height = 1080;
	this->videoMode.width = 1920;
	this->window.create(this->videoMode, "Platformer");
	this->window.setFramerateLimit(60);
}

/*
	Create playable character
*/
void Game::initPlayer()
{
	this->player = new Player();
}

/*
	Create tiles for current level
*/
void Game::initTileMap()
{
	this->tile = new TileMap("Level1.txt");
}

/*
	Constructor for game loop
	Initialize all objects for level
*/
Game::Game()
{
	this->initWindow(); 
	this->initPlayer();
	this->initTileMap();
}

/*
	Destructor for game loop
*/
Game::~Game()
{
	delete this->player;
}

/*
	Call player's update function to apply forces, and change textures
*/
void Game::updatePlayer()
{
	this->player->update();
}

/*
	Change what tiles are on the window
*/
void Game::updateTileMap()
{
	this->tile->update();
}

/*
	Check if player is colliding with top or bottom of tiles
*/
void Game::updateGroundCollision()
{
	FloatRect playerBounds = this->player->getGlobalBounds(); //hitbox of player
	FloatRect wallBounds; // hitbox for each tile
	//Go through all tiles in map
	for (int i = 0; i < tile->loadCounter.x; i++) {
		for (int j = 0; j < tile->loadCounter.y; j++) {
			wallBounds = tile->tiles[i][j]->getGlobalBounds(); //set hitbox to tile at position

			//Check how to handle collision will world
			if (wallBounds.intersects(playerBounds)) {
				//Player is underneath block
				if (wallBounds.top <= playerBounds.top) {
					this->player->resetVelocityY();
					this->player->setCanJump(false);
				}

				//Player is above block
				else if(wallBounds.top >= (playerBounds.top)){
					this->player->resetVelocityY(); //set player velocity to 0
					this->player->setCanJump(true); //allow player to jump
					this->player->setOnGround(true); //set player as on the ground
					this->player->setPosition(
						this->player->getPosition().x,
						wallBounds.top - this->player->getGlobalBounds().height
					); // set player to be right above ground tile
				}
			}
			this->player->setOnGround(false); //When player is no longer on a block, allow falling
		}
	}
}

/*
	Check if player is colliding with vertical walls
*/
void Game::updateWallCollision()
{
	FloatRect playerBounds = this->player->getGlobalBounds(); //hitbox of player
	FloatRect wallBounds; //hitbox for each tile
	//Go through all tiles in map
	for (int i = 0; i < tile->loadCounter.x; i++) {
		for (int j = 0; j < tile->loadCounter.y; j++) {
			wallBounds = tile->tiles[i][j]->getGlobalBounds(); //set hitbox to tile at current position

			//Check how to handle collision will world
			if (wallBounds.intersects(playerBounds) && wallBounds.top <= playerBounds.top) {
				//if player is moving left and colliding with left wall, move player right
				if (this->player->getFaceLeft() == true)
					this->player->move(10.f, 0.f);
				//if player is moving right and colliding with right wall, move player left
				else
					this->player->move(-10.f, 0.f);
			}
		}
	}

}


/*
	Check is player reached top or bottom of window
*/
void Game::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height
		> this->window.getSize().y)
	{
		this->player->resetVelocityY(); //set player speed to 0
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		); //set player position to right above bottom of window
		this->player->setCanJump(true); //player can jump
		this->player->setOnGround(true); //player is on the ground
	}
	//Collision with Ceiling
	else if (this->player->getPosition().y + this->player->getGlobalBounds().height
		<= this->player->getGlobalBounds().height) {
		this->player->resetVelocityY(); //set player speed to 0
		this->player->setCanJump(false); //player cannot jump
	}
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev)) {
		//Events to close window
		if (this->ev.type == Event::Closed)
			this->window.close();
		else if (this->ev.type == Event::KeyPressed &&
			this->ev.key.code == Keyboard::Escape)
			this->window.close();

		//Keys pressed for character movement
		if (
			this->ev.type == Event::KeyReleased &&
			(
				this->ev.key.code == Keyboard::A ||
				this->ev.key.code == Keyboard::S ||
				this->ev.key.code == Keyboard::W ||
				this->ev.key.code == Keyboard::D
				)
			) 
		{
			this->player->resetAnimationTimer(); //reset how long animation has been playing
		}
	}

	//Update all images on screen
	this->updatePlayer();
	this->updateTileMap();
	this->updateGroundCollision();
	this->updateWallCollision();
	this->updateCollision();
}

/*
	Draw player to window
*/
void Game::renderPlayer()
{
	this->player->render(this->window);
}

/*
	Draw tiles to window
*/
void Game::renderTileMap()
{
	this->tile->render(this->window);
}


/*
	Draw all objects to window
*/
void Game::render()
{
	this->window.clear();

	//Render game objects
	this->renderPlayer();
	this->renderTileMap();

	this->window.display();
}

/*
	Get reference to game window
*/
const RenderWindow& Game::getWindow()
{
	return this->window;
}


