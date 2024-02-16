#include "TextureManager.h"

/// Function to load a texture from file and store it with a given id
bool TextureManager::loadTexture(const char* fileName, std::string id, SDL_Renderer* ren) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);/*!< Load image file as a surface*/

	/// Check if the surface was successfully loaded
	if (tmpSurface == 0) {
		std::cout << "tmpSurface not created!" << std::endl;
		return false;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tmpSurface);/*!< Create a texture from the surface*/
	SDL_FreeSurface(tmpSurface);/*!< Free the temporary surface*/

	/// Check if the texture was successfully created
	if (tex != 0) {
		textureMap[id] = tex;/*!< Store the texture in the texture map with the given id*/
		return true;
	}

	return false;
}

/// Function to draw a texture at a specified position with a given size and flip mode
void TextureManager::drawTexture(std::string id, int xpos, int ypos, int width, int height, SDL_Renderer* ren, SDL_RendererFlip flip) {
	
	/// Set up source and destination rectangles for rendering
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = xpos;
	destRect.y = ypos;

	/// Render the texture to the screen
	SDL_RenderCopyEx(ren, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

/// Function to draw a filled rectangle on the renderer
void TextureManager::drawRecnatgle(SDL_Renderer* renderer, int xpos, int ypos, int width, int height) {
	SDL_Rect fillRect = { xpos, ypos, width, height };/*!< Create a rectangle to fill*/
	
	/// Set the render draw color and fill the rectangle
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
	SDL_RenderFillRect(renderer, &fillRect);
}

/// Static method to get the singleton instance of TextureManager
TextureManager* TextureManager::Instance() {

	/// If instance is null, create a new TextureManager and return it
	if (instance == 0) {
		instance = new TextureManager();

		return instance;
	}

	return instance;
}

/// Initialize the instance pointer to null
TextureManager* TextureManager::instance = 0;
