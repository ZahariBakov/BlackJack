#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) 
{
	//srand(time(0));
	                  
	game = new Game();

	game->Init("Come and lose some money!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0);

	while (game->IsRunning()) 
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	game->Clean();

	return 0;
}
