#include "Player.h"

void Player::initVariables()
{
	this->animState = IDLE;
	this->canJump = true;
	this->onGround = false;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("images/player_sheet.png"))
		std::cout << "Error Could not load player sheet";
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = IntRect(0, 0, 40, 50);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(1.f, 1.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 20.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.85f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}	

Player::~Player()
{
}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animSwitch;
	if (this->animSwitch)
		this->animSwitch = false;

	return anim_switch;
}

const Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const bool Player::getCanJump() const
{
	return this->canJump;
}

const bool Player::getOnGround() const
{
	return this->onGround;
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::setCanJump(bool jump)
{
	this->canJump = jump;
}

void Player::setOnGround(bool ground)
{
	this->onGround = ground;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;
	this->velocity.y += dir_y * this->acceleration;

	//Limit Velocity
	if (abs(this->velocity.x) > this->velocityMax) {
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics()
{
	//Gravity
	if (!onGround) {
		this->velocity.y += 1 * this->gravity;
	}
	//Limit gravity
	if (abs(this->velocity.y) > this->velocityMaxY) {
		this->velocity.y = this->velocityMaxY* ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}
	//Deceleration
	this->velocity *= this->drag;

	//Limit Deceleration
	if (abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animState = IDLE;
	if (Keyboard::isKeyPressed(Keyboard::A)) //Left
	{
		this->move(-1.f, 0.f);
		this->animState = MOVING_LEFT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) //Right
	{
		this->move(1.f, 0.f);
		this->animState = MOVING_RIGHT;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && this->canJump) //Jump
	{
		this->move(0.f, -10.f);
		this->animState = JUMPING;
	}
	/*else if (Keyboard::isKeyPressed(Keyboard::W)) //Up
	{
		this->sprite.move(0.f, -1.f);


	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) //Down
	{
		this->sprite.move(0.f, 1.f);

	}*/
}

void Player::updateAnimations()
{
	if (this->animState == IDLE) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 160.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == MOVING_RIGHT) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}			
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == MOVING_LEFT) {
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-1.f, 1.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.f, 0.f);
	}
	else
		this->animationTimer.restart();
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
