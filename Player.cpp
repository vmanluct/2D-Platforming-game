#include "Player.h"

/*
	Initialize what animation state player is in
	Allow player to jump initially
	Set player as not on ground initially
	Set player initially facing right
*/
void Player::initVariables()
{
	this->animState = IDLE;
	this->canJump = true;
	this->onGround = false;
	this->faceLeft = false;
}

/*
	Initialize texture sheet for player
	Write error to terminal if file is not found
*/
void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("images/spritesheet.png"))
		std::cout << "Error Could not load player sheet";
}

/*
	Initialize player sprite
	Starting texture
	How big player is
*/
void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet); //set sprite as texture sheet
	this->currentFrame = IntRect(0, 0, 64, 64); //start sprite at first texture in sheet
	this->sprite.setTextureRect(this->currentFrame); 
	this->sprite.setScale(1.f, 1.f); //set player to 1 to 1 scale
}

/*
	Initialize what texture to start player in
*/
void Player::initAnimations()
{
	this->animationTimer.restart(); //restart timer for each animation
	this->animSwitch = true; //allow textures to cycle through
}

/*
	Initialize all max and min velocity for x and y direction
	Initialize drag, acceleration, and gravity
*/
void Player::initPhysics()
{
	this->velocityMax = 20.f; //max speed player can move left and right
	this->velocityMin = 1.f; //min speed player can move left and right
	this->acceleration = 3.f; //how fast player velocity increases or decreases
	this->drag = 0.85f; //what percent to multiply speed by
	this->gravity = 4.f; //gravity applied to bring player to ground
	this->velocityMaxY = 100.f; //max velocity in y direction player can move
}

/*
	Player Constructor
	Initialize all properties for player
*/
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}	

/*
	Player destructor
*/
Player::~Player()
{
}

/*
	Check if sprite should move to next texture
*/
const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animSwitch;
	if (this->animSwitch)
		this->animSwitch = false;

	return anim_switch;
}

/*
	Get how fast player is moving x and y direction
*/
const Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

/*
	Get hitbox of player
*/
const FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

/*
	Get if player can jump
*/
const bool Player::getCanJump() const
{
	return this->canJump;
}

/*
	Get if player is on the ground
*/
const bool Player::getOnGround() const
{
	return this->onGround;
}

/*
	Get what direction player is facing
*/
const bool Player::getFaceLeft() const
{
	return this->faceLeft;
}

/*
	Set where player is on screen
*/
void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

/*
	Set player move speed to 0
*/
void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

/*
	Set player can jump
	True is player is on the ground
	False otherwise
*/
void Player::setCanJump(bool jump)
{
	this->canJump = jump;
}

/*
	Set if player is on the ground
	True is player bottom hitbox overlaps top of tile sprite
	False otherwise
*/
void Player::setOnGround(bool ground)
{
	this->onGround = ground;
}

/*
	Set what direction player is facing
	True if velocity x is less than 0
	False otherwise
*/
void Player::setFaceLeft(bool direction)
{
	this->faceLeft = direction;
}


/*
	Reset timer for how long each texture has been active
	Allow texture to be changed
*/
void Player::resetAnimationTimer()
{
	this->animationTimer.restart(); //reset timer for how long to stay in texture
	this->animSwitch = true; //allow sprite to change to next texture
}

/*
	Apply given velocities to both x, and y direction
	If new velocities are greater than max values, limit them
*/
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

/*
	Physics system
	If player is not on ground apply gravity
	If speed falling down is too fast limit y velocity
	Slow down player when moving left and right
*/
void Player::updatePhysics()
{
	//Gravity
	if (!onGround) {
		this->velocity.y += 0.5 * this->gravity;
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

	//Move player given the velocity after applying physics
	this->sprite.move(this->velocity);
}

/*
	Change movement of player depending on button pressed
*/
void Player::updateMovement()
{
	this->animState = IDLE;
	if (Keyboard::isKeyPressed(Keyboard::A)) //Left
	{
		this->move(-1.f, 0.f);
		this->animState = MOVING_LEFT;
		this->faceLeft = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) //Right
	{
		this->move(1.f, 0.f);
		this->animState = MOVING_RIGHT;
		this->faceLeft = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && this->canJump) //Jump
	{
		float jumpHeight = -sqrtf(2.f * gravity + 350.f);
		this->move(0.f, jumpHeight);
		this->animState = JUMPING;
		this->canJump = false;
	}
}

/*
	Change through different textures depending on actions of player
*/
void Player::updateAnimations()
{
	//Not moving
	if (this->animState == IDLE) {
		//Add delay to how often cycle through idle textures
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f; //set height of texture sheet to idle row
			this->currentFrame.left += 64.f; //move which texture is showed
			if (this->currentFrame.left >= 256.f) //if left point reaches end of row reset textures
				this->currentFrame.left = 0;

			this->animationTimer.restart(); //reset timer for animations
			this->sprite.setTextureRect(this->currentFrame); //set sprite as current frame
		}
	}
	//Moving right
	else if (this->animState == MOVING_RIGHT) {
		//Delay
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 64.f; //Height of moving texture row
			this->currentFrame.left += 64.f; //move through moving texture row
			if (this->currentFrame.left >= 256.f) //if reached last texture reset position
				this->currentFrame.left = 0.f;

			this->animationTimer.restart(); //reset timer for animations
			this->sprite.setTextureRect(this->currentFrame); //set sprite as current texture
		}			
		this->sprite.setScale(1.f, 1.f); //set scale 1 to 1
		this->sprite.setOrigin(0.f, 0.f); //set rotation point to center of sprite
	}
	//Moving left
	else if (this->animState == MOVING_LEFT) {
		//Delay
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 64.f; //height of moving texture
			this->currentFrame.left += 64.f; //move through moving texture row
			if (this->currentFrame.left >= 256.f) //if reached last texture, reset position
				this->currentFrame.left = 0.f;

			this->animationTimer.restart(); //reset timer for animations
			this->sprite.setTextureRect(this->currentFrame); //set sprite as current texture
		}
		this->sprite.setScale(-1.f, 1.f); //set scale 1 to 1
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.f, 0.f); //flip sprite at center
	}

	//reset animation timer
	else
		this->animationTimer.restart();
}

/*
	Move player, and change texture for sprite
*/
void Player::update()
{
	this->updateMovement(); //apply velocities to player
	this->updateAnimations(); //apply texture to player
	this->updatePhysics(); //update physics being applied
}

/*
	Draw player to screen
*/
void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}
