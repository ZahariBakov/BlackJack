#pragma once

#include "Game.h"/*!< Include neessary header for Game class*/

#include <map>

class TextureManager {
public:
	/// Function to load a texture from file and store it with a given ID 
	bool loadTexture(const char* fileName, std::string id, SDL_Renderer* ren);

	/// Function to draw a texture at a specified position with a given size and flip mode
	void drawTexture(std::string id, int xpos, int ypos, int width, int height, SDL_Renderer* ren, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	/// Static method to draw a rectangle using the SDL_Renderer
	static void drawRecnatgle(SDL_Renderer* renderer, int xpos, int ypos, int width, int height);

	/// Static method to get the singleton instance of TextureManager
	static TextureManager* Instance();

private:
	std::map<std::string, SDL_Texture*> textureMap;/*!< Map to store loaded textures*/
	TextureManager() {}/*!< Private constructor to enforce singleton pattern*/
	static TextureManager* instance;/*!< Pointer to the singleton instance*/
};
