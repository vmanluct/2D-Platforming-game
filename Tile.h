#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Tile
{
private:
	Sprite sprite;
	const bool damaging;

public:
	Tile(Texture& texture_sheet, IntRect texture_rect, bool damaging = false);

	const FloatRect getGlobalBounds() const;

	void update();
	void render(RenderTarget &target);
};

