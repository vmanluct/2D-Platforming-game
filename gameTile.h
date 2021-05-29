#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#ifndef GAMETILE_H
#define GAMETILE_H

using namespace std;
using namespace sf;
class gameTile
{
public:
	bool isPassable;
	bool isExit;
	Vector2f pos;
	Texture texture;
	Sprite sprite;

	gameTile(string, float, float, bool, bool);
	bool setUpSprite(string);
};


#endif
