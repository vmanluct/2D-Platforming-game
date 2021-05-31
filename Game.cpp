#include "Game.h"


void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window.create(this->videoMode, "Platformer");
	this->window.setFramerateLimit(60);
}


void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initTileMap()
{
	this->tile = new TileMap();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initTileMap();
}

Game::~Game()
{
	delete this->player;
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateTileMap()
{
	this->tile->update();
}

void Game::updateWallCollision()
{
	FloatRect playerBounds = this->player->getGlobalBounds();
	FloatRect wallBounds;
	for (int i = 0; i < tile->loadCounter.x; i++) {
		for (int j = 0; j < tile->loadCounter.y; j++) {
			wallBounds = tile->tiles[i][j]->getGlobalBounds();

			//Check how to handle collision will world
			if (wallBounds.intersects(playerBounds)) {
				//Player is underneath block
				if (wallBounds.top <= playerBounds.top) {
					this->player->resetVelocityY();
					this->player->setCanJump(false);
				}

				//Player is above block
				else {
					this->player->resetVelocityY();
					this->player->setCanJump(true);
					this->player->setOnGround(true);
					this->player->setPosition(
						this->player->getPosition().x,
						wallBounds.top - this->player->getGlobalBounds().height
					);
				}
			}
			this->player->setOnGround(false); //When player is no longer on a block, allow falling
		}
	}
}

void Game::updateCollision()
{
	//Collision bottom of screen
	if (this->player->getPosition().y + this->player->getGlobalBounds().height
		> this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		);
		this->player->setCanJump(true);
	}
	//Collision with Ceiling
	else if (this->player->getPosition().y + this->player->getGlobalBounds().height
		<= this->player->getGlobalBounds().height) {
		this->player->resetVelocityY();
		this->player->setCanJump(false);
	}
}

void Game::update()
{
	//Polling window events
	while (this->window.pollEvent(this->ev)) {
		if (this->ev.type == Event::Closed)
			this->window.close();
		else if (this->ev.type == Event::KeyPressed &&
			this->ev.key.code == Keyboard::Escape)
			this->window.close();

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
			this->player->resetAnimationTimer();
		}
	}

	//Update all images on screen
	this->updatePlayer();
	this->updateTileMap();
	this->updateWallCollision();
	this->updateCollision();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderTileMap()
{
	this->tile->render(this->window);
}


void Game::render()
{
	this->window.clear();

	//Render game objects
	this->renderPlayer();
	this->renderTileMap();

	this->window.display();
}

const RenderWindow& Game::getWindow()
{
	return this->window;
}


