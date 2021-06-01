#include "Tile.h"

/*
	Tile constructor
	Get reference to loaded texture
	Set what texture in sheet is used
	Set whether block should damage player
*/
Tile::Tile(Texture& texture_sheet, IntRect texture_rect, bool damaging)
	:damaging(damaging)
{
	this->sprite.setTexture(texture_sheet); //set sprite to texture sheet
	this->sprite.setTextureRect(texture_rect); //set which texture in sheet is used
}

/*
	Get hitbox for tile
*/
const FloatRect Tile::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

/*
	Update position and texture for tile
*/
void Tile::update()
{
}

/*
	Draw tile to screen
*/
void Tile::render(RenderTarget& target)
{
	target.draw(this->sprite);
}

