#include "Game.h"

Game* game = NULL;/*!< Initialize a game variable with value NULL*/

///Screen dimensions.
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 550;

int main(int argc, char* argv[]) {
	srand(time(0));   /*!< Generate random numbers*/
	                  
	game = new Game();/*!< Create new game object*/

	/// Call the init function of the game object
	game->init("Come and lose some money!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	/// Loop when the game is running
	while (game->isRunning()) {
		game->handleEvents();/*!< Process events*/
		game->ttf_init();    /*!< Call the ttf_init function of the game object*/
		game->update();      /*!< Update game logic*/
		game->render();      /*!< Render graphics*/
	}

	/// When the game is finished, call the clean function on the game object.
	game->clean();

	/// After completing all the processes
	return 0;
}
