#include "Game.h"

Game* game = NULL;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 550;

int main(int argc, char* argv[]) {
	srand(time(0));
	                  
	game = new Game();

	game->Init("Come and lose some money!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	while (game->IsRunning()) {
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	game->Clean();

	return 0;
}
