#include "Player.h"
#include "Game.h"

using namespace sf;
int main() {
	srand(static_cast<unsigned>(time(0)));

	//Init Game Engine
	Game game;

	while (game.getWindow().isOpen()) {

		game.update();
		game.render();

	}
	return 0;
}