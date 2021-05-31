#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum  PLAYER_ANIMATION_STATES{IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING };


using namespace sf;
class Player
{
private:
	Sprite sprite;
	Texture textureSheet;
	Clock animationTimer;

	//Animation
	short animState;
	IntRect currentFrame;
	bool animSwitch;

	//Physics
	Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;
	bool canJump;
	bool onGround;

	//Core

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player();
	virtual ~Player();



	//Accssors
	const bool& getAnimSwitch();
	const Vector2f getPosition() const;
	const FloatRect getGlobalBounds() const;
	const bool getCanJump() const;
	const bool getOnGround() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void setCanJump(bool jump);
	void setOnGround(bool ground);


	//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(RenderTarget& target);
};

