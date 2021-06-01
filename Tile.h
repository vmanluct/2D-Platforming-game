#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Tile
{
private:

	const bool damaging; //if the tile will hurt the player when overlapped

public:
	Sprite sprite; //sprite for the tile

	Tile() :damaging(false){
		//Default constructor

	}

	//Constructor to set texture, and if the tile should damage the player
	Tile(Texture& texture_sheet, IntRect texture_rect, bool damaging = false);

	const FloatRect getGlobalBounds() const; //Hitbox for tile

	void update(); //update texture for tile
	void render(RenderTarget &target); //draw tile to screen
};

