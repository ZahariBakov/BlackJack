#include "Game.h"

Game* game = NULL;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 550;

int main(int argc, char* argv[]) {
	srand(time(0));
	                  
	game = new Game();

	game->init("Come and lose some money!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	game->ttf_init();

	while (game->isRunning()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}
