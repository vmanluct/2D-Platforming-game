#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum  PLAYER_ANIMATION_STATES{IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING };


using namespace sf;
class Player
{
private:
	Sprite sprite; //player sprite
	Texture textureSheet; //texture with all animations for player
	Clock animationTimer; //timer to see how long each animation has gone

	//Animation
	short animState; //what animation state player is in
	IntRect currentFrame; //rectangle to determine what texture is displayed
	bool animSwitch; //if the next animation should be played

	//Physics
	Vector2f velocity; //velocity of player
	float velocityMax; //limiting value for velocity
	float velocityMin; 
	float acceleration; //value for how to accelerate player
	float drag; //value to limit and slow down player
	float gravity; 
	float velocityMaxY; //max Y force to limit gravity and jump height
	bool canJump; //if the player can jump
	bool onGround; //if the player is on the ground
	bool faceLeft; //what direction player is facing


	//Initializers
	void initVariables(); 
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player(); //Constructor
	virtual ~Player(); //Destructor



	//Accssors
	const bool& getAnimSwitch(); //get what animation state player is in
	const Vector2f getPosition() const; //get current position of player
	const FloatRect getGlobalBounds() const; //get hitbox for player
	const bool getCanJump() const; //check if player can jump
	const bool getOnGround() const; //check if player is on the ground
	const bool getFaceLeft() const; //check if player is facing left


	//Modifiers
	void setPosition(const float x, const float y); //set position of player
	void resetVelocityY(); //set velocity of player to 0
	void setCanJump(bool jump); //set if player can jump
	void setOnGround(bool ground); //set if player is on the ground
	void setFaceLeft(bool direction); //set what direction player is facing



	//Functions
	void resetAnimationTimer(); //reset timer for animation state
	void move(const float dir_x, const float dir_y); //control movement of player
	void updatePhysics(); //apply gravity, and velocities to the player
	void updateMovement(); // use velocities to update speed of player
	void updateAnimations(); //change the animation based on player's action
	void update(); //move player to new position
	void render(RenderTarget& target); //draw player to window
};

