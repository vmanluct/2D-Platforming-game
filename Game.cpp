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

Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}

void Game::updatePlayer()
{
	this->player->update();
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
	this->updatePlayer();
	this->updateCollision();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();

	//Render game objects
	this->renderPlayer();

	this->window.display();
}

const RenderWindow& Game::getWindow()
{
	return this->window;
}


